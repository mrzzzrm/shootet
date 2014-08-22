#include "Level.hpp"

using namespace std;

using namespace util;
using namespace etc;
using namespace geo;
using namespace gfx;
using namespace input;
using namespace particle;
using namespace error;
using namespace tmx::base;
using namespace tmx::render;





Level::Level()
{
  score = 0;
}


Level::~Level()
{
  clear();
}


void Level::load(const Path &path, LEVEL_DIFFICULTY difficulty, int number)
{
  clear();

  Map::load(path);

  /* Init */
    this->number = number;
    this->difficulty = difficulty;

    state = LEVEL_SCENE_INTRO;
    eruption_until = 0;
    desthalt_until = 0;
    stop_until = 0;
    rapidfire_until = 0;

    handlemap_lastcheck.load(-1, -1);

    map_tile_range_y = (double)MAP_RANGE_Y / Map::getTileHeight();


  /* Verify Map */
    if(Map::getLayerCount() != 1 || Map::getLayer(0).getType() != LAYER_TILELAYER)
      throw Exception() << "Map is supposed to have exactly one tilelayer. Illegal layercount or type.";
    if(Map::getWidth() == 0 || Map::getHeight() == 0)
      throw Exception() << "Illegal mapsize";
    if(Map::getTileWidth() == 0 || Map::getTileHeight() == 0)
      throw Exception() << "Illegal tilesize";


  /* Read properties */
    try
    {
      speed = string_to_float(Map::getProperties().getValue("speed"));
    }
    catch(Exception &exception)
    {
      throw Exception() << "Error whilst loading properties: " << exception.getDescription();
    }


  /* Load background */
    try
    {
      background.load(Path(path.getDirectory()).append(Map::getProperties().getValue("background")));
        background.removeColorkey();
    }
    catch(Exception &exception)
    {
      throw Exception() << "Error whilst loading background: " << exception.getDescription();
    }


  /* Setup particlemanager */
    ParticleProfile *pprofile = new ParticleProfile();
      pprofile->addFrame(ParticleFrame(ImageClipping(&media::gfx::particle, IntRect(0, 0, 6, 6)), 0.5));
      pprofile->addFrame(ParticleFrame(ImageClipping(&media::gfx::particle, IntRect(6, 0, 4, 4)), 0.5));
      pprofile->addFrame(ParticleFrame(ImageClipping(&media::gfx::particle, IntRect(10, 0, 3, 3)), 1.0));
      pprofile->addFrame(ParticleFrame(ImageClipping(&media::gfx::particle, IntRect(13, 0, 3, 3)), 1.0));
      pprofile->addFrame(ParticleFrame(ImageClipping(&media::gfx::particle, IntRect(16, 0, 2, 2)), 1.0));
      pprofile->addFrame(ParticleFrame(ImageClipping(&media::gfx::particle, IntRect(19, 0, 1, 1)), 1.0));

    particlemanager.setParticleProfile(0, pprofile);


  /* Setup player */
    player.setX(Map::getWidth()/2);
    player.setY(Map::getHeight() + ((double)Player::getHeight()/(double)Map::getTileHeight())/2);
    player.setColumnCount(Map::getWidth());


  /* Setup camera */
    camera.setPosition(FloatPoint(0, Map::getHeight() - map_tile_range_y + PLAYER_OFFSET));
}


void Level::clear()
{
  list_delete_all_and_clear(rocketlist);
  list_delete_all_and_clear(quadlist);
  list_delete_all_and_clear(itemlist);
}


int Level::getScore() const
{
  return score;
}


double Level::getSpeed() const
{
  return speed;
}


LEVEL_DIFFICULTY Level::getDifficulty() const
{
  return difficulty;
}


int Level::getNumber() const
{
  return number;
}


LEVEL_STATE Level::getState() const
{
  return state;
}


Player &Level::getPlayer()
{
  return player;
}


Multiplier &Level::getMultiplier()
{
  return multiplier;
}


Camera &Level::getCamera()
{
  return camera;
}


ParticleManager &Level::getParticleManager()
{
  return particlemanager;
}


void Level::setState(LEVEL_STATE state)
{
  this->state = state;
}


void Level::run()
{
  Timer::run();

  player.run();
  multiplier.run();
}


void Level::pause()
{
  Timer::pause();

  player.pause();
  multiplier.pause();
}


void Level::update()
{
  Timer::update();

  switch(state)
  {
    case LEVEL_PLAYING:

      HandlePlayer();
      HandleMap();
      HandleCamera();
      HandleMultiplier();


    case LEVEL_PAUSED:
    case LEVEL_SCENE_INTRO:
    case LEVEL_SCENE_FAILURE:
    case LEVEL_SCENE_SUCCESS:
    case LEVEL_SCENE_QUIT:

      HandleQuads();
      HandleEruption();
      HandleParticles();
      HandleRockets();
      HandleItems();
  }
}


void Level::draw()
{
  DrawBackground();
  DrawMap();

  DrawQuads();

  if(state != LEVEL_SCENE_FAILURE)
    DrawPlayer();

  if(state != LEVEL_SCENE_INTRO)
    DrawCursor();

  DrawRockets();
  DrawItems();
  DrawParticles();
}


void Level::HandleEruption()
{
  if(Timer::getTicks() <= eruption_until)
  {
    FloatVector offset;
    double dist, deg;
    dist = (((double)eruption_until - (double)Timer::getTicks()) / (double)ERUPTION_TIME_MAX) * ERUPTION_OFFSET_MAX;
    deg = FloatRandom(2 * M_PI);

    offset.setX(cos(deg) * dist);
    offset.setY(-sin(deg) * dist);
    camera.setOffset(offset);
  }
}


void Level::HandleQuads()
{
  for(list<Quad*>::iterator i = quadlist.begin(); i != quadlist.end();)
  {
    if(HandleQuadMovement(*i))
      i = list_erase_and_delete(quadlist, i);
    else
      i++;
  }
}


bool Level::HandleQuadMovement(Quad *quad)
{
  double step, total;

  total = - Timer::getPerSecond(QUAD_SPEED + speed);

  if(rapidfire_until >= Timer::getTicks())
    total = - Timer::getPerSecond(QUAD_RAPIDFIRE_SPEED + speed);
  else
    total = - Timer::getPerSecond(QUAD_SPEED + speed);


  for(; total != 0; total -= step)
  {
    step = abs_min((double)sgn(total), total);

    quad->incY(step);

    if(HandleQuadMapInteraction(quad))
      return true;

    /* Delete quad if it is out of display */
      if((quad->getY() - camera.getY()) * Map::getTileHeight() + Map::getTileHeight()/2 < 0)
        return true;
      else
        return false;
  }

  return false;
}


bool Level::HandleQuadMapInteraction(Quad *quad)
{
  int x, y;

  x = (int)(quad->getX());
  y = (int)(quad->getY() - 0.5);

  if(isTile(x, y))
  {
    int score;
    IntRect block;

    AppendTile(x, y + 1);

    block = RemoveTileBlock(x, y + 1);

    score = ScoreEffect(block);
    SpecialEffect(block, score);
    GraphicEffect(block, score);
    AudioEffect(block);

    this->score += score;

    return true;
  }

  return false;
}


void Level::AppendTile(int x, int y)
{
  MorphTile mo(getTile(x, y - 1) - 1);
  MorphTile mu(QUAD_TILE_ID);


  /* Left side */
    if(isTile(x - 1, y) && isTile(x - 1, y - 1))
    {
      MorphTile lt(getTile(x - 1, y - 1) - 1);
      MorphTile lb(getTile(x - 1, y) - 1);

      if(lt.isRightOpen() && lb.isTopOpen())
      {
        lt.setNode(3, 0);
        lt.setNode(4, 0);

        lb.setNode(1, 0);
        lb.setNode(2, 0);
        lb.setNode(3, 1);

        mo.setNode(5, 0);
        mo.setNode(6, 0);

        mu.setNode(6, lb.getNode(3));
        mu.setNode(7, lb.getNode(2));

        setTile(x - 1, y - 1, lt.getId() + 1);
        setTile(x - 1, y, lb.getId() + 1);
      }
      else
      {
        mo.setNode(5, 1);
      }
    }
    else
    {
      mo.setNode(5, 1);
    }

  /* Right side */
    if(isTile(x + 1, y) && isTile(x + 1, y - 1))
    {
      MorphTile ru(getTile(x + 1, y - 1) - 1);
      MorphTile rb(getTile(x + 1, y) - 1);

      if(ru.isLeftOpen() && rb.isTopOpen())
      {
        ru.setNode(5, 0);
        ru.setNode(6, 0);

        rb.setNode(6, 1);
        rb.setNode(7, 0);
        rb.setNode(0, 0);

        mo.setNode(3, 0);
        mo.setNode(4, 0);

        mu.setNode(2, rb.getNode(7));
        mu.setNode(3, rb.getNode(6));

        setTile(x + 1, y - 1, ru.getId() + 1);
        setTile(x + 1, y, rb.getId() + 1);
      }
      else
      {
        mo.setNode(4, 1);
      }
    }
    else
    {
      mo.setNode(4, 1);
    }


  /* Middle */
    mu.setNode(0, mo.getNode(5));
    mu.setNode(1, mo.getNode(4));

    setTile(x, y, mu.getId() + 1);
    setTile(x, y - 1, mo.getId() + 1);
}


IntRect Level::RemoveTileBlock(int stx, int sty)
{
  bool bridge;
  int bx;
  int w, wtot;
  int xmin, xmax;
  int ymin, ymax;

  ymin = sty;

  /* Detect bottom range */
    for(xmin = stx; ; xmin--)
    {
      MorphTile mt(0);

      if(!isTile((int)xmin - 1, sty))
        break;

      mt.setId(getTile((int)xmin - 1, sty) - 1);

      if(mt.isBottomOpen())
        break;
    }

    for(xmax = stx; ; xmax++)
    {
      MorphTile mt(0);

      if(!isTile((int)xmax + 1, sty))
        break;

      mt.setId(getTile((int)xmax + 1, sty) - 1);

      if(mt.isBottomOpen())
        break;
    }


  /* Detect biggest possible width */
    wtot =  xmax - xmin + 1;
    bridge = false;
    for(w = wtot; w > 0; w--)
    {

      for(bx = xmin; bx <= xmin + wtot - w; bx++)
      {
        MorphTile mtl(getTile(bx, sty) - 1);
        MorphTile mtr(getTile(bx + w - 1, sty) - 1);

        /* Check if the given range is possible */
          if(mtl.isLeftOpen() || mtr.isRightOpen())
            continue;

        /* Move up as far as possible */
          for(ymin = sty; ; ymin--)
          {
            if(isTile(bx, ymin - 1) && isTile(bx + w - 1, ymin - 1))
            {
              MorphTile mtl(getTile(bx        , ymin - 1) - 1);
              MorphTile mtr(getTile(bx + w - 1, ymin - 1) - 1);

              if(mtl.isLeftOpen() || mtr.isRightOpen())
                break;
            }
            else
            {
              break;
            }
          }

        /* Move down and find bridge between left and right */
          for(;sty - ymin > 0; ymin++)
          {
            bridge = true;

            for(int x = bx; x < bx + w; x++)
            {
              if(isTile(x, ymin))
              {
                MorphTile mt(getTile(x, ymin) - 1);

                if(mt.isTopOpen())
                {
                  bridge = false;
                  break;
                }
              }
              else
              {
                bridge = false;
                break;
              }
            }

            if(bridge)
            {
              break;
            }
          }

        if(bridge)
          break;
      }

      if(bridge)
        break;
    }

    if(w == 0)
      return IntRect(0, 0, 0, 0);

    xmin = bx;
    xmax = bx + w - 1;
    ymax = sty;


  /* Remove tiles in range */
    for(int x = xmin; x <= xmax; x++)
    {
      for(int y = ymin; y <= ymax; y++)
      {
        setTile(x, y, 0);
      }
    }


  /* Return */
    return IntRect(xmin, ymin, xmax - xmin + 1, ymax - ymin + 1);
}


int Level::ScoreEffect(const IntRect &rect)
{
  double factor;
  int size;


  size = rect.getWidth() * rect.getHeight();
  factor = SCORE_SIZE_FACTOR * pow(size, (double)2) + SCORE_PER_TILE * size;

  return (int)(factor * multiplier.getFactor());
}


void Level::SpecialEffect(const IntRect &rect, int score)
{
  int size;


  size = rect.getWidth() * rect.getHeight();

  /* No tiles, no effect */
    if(size == 0)
      return;

  /* Items */
    for(int i = 0; i < ITEM_TYPE_END; i++)
    {
      if(size >= ITEM_REQUIRED_DESTRUCTION[i] && player.getItemCount((ITEM_TYPE)i) < ITEM_COUNT_LIMIT[i])
      {
        FloatPoint position;

        position.setX(rect.getX() + rect.getWidth()/2);
        position.setY(rect.getY() + rect.getHeight()/2);

        itemlist.push_back(new Item((ITEM_TYPE)i, position));

        break;
      }
    }


  /* Destruction halt */
    desthalt_until = Timer::getTicks() + (int)min(size * DESTHALT_PER_TILE, DESTHALT_MAX);


  /* Multiplier */
    if(size >= MULTIPLIER_MIN_DESTRUCTION)
      multiplier.setFilling(multiplier.getFilling() + score/multiplier.getFactor());
}


void Level::GraphicEffect(const IntRect &rect, int score)
{
  /* Explosion */
  for(int x = rect.getX(); (int)x < rect.getWidth() + rect.getX(); x++)
  {
    for(int y = rect.getY(); (int)y < rect.getHeight() + rect.getY(); y++)
    {
      explodeTile(x, y);
    }
  }

  /* Eruption */
  if(rect.getWidth() * rect.getHeight() > 0)
  {
    eruption_until = Timer::getTicks() + min(rect.getWidth() * rect.getHeight() * ERUPTION_TIME_PER_TILE, ERUPTION_TIME_MAX);
  }
}


void Level::AudioEffect(int size)
{
  if(size == 0)
    return;

  for(int min = 2-1; min >= 0; min--)
  {

    if(size >= SFX_BLOCK_EXPLOSION_MINIMUM[min])
    {

      media::sfx::block_explosion[min + 1].play();
      return;
    }
  }

  media::sfx::block_explosion[0].play();

}


void Level::AudioEffect(const geo::IntRect &rect)
{
  AudioEffect(rect.getWidth() * rect.getHeight());
}



void Level::HandlePlayer()
{
  player.update();

  HandlePlayerMovement();
  HandlePlayerAction();
}


void Level::HandlePlayerMovement()
{
  bool found;
  double step, total;


  if(Input::isButtonHold(BUTTON_UP))
  {
    total = - Timer::getPerSecond(speed + PLAYER_BUTTON_UP_EXTRA_SPEED);
  }
  else
  {
    total = - Timer::getPerSecond(speed);

    if(stop_until >= Timer::getTicks())
      total = 0;

    if(desthalt_until >= Timer::getTicks())
      total = 0;
  }

  /* Check for blocks on screen */
  found = false;
  for(int y = (int)camera.getY() + 2; y < (int)camera.getY() + (int)map_tile_range_y; y++)
  {
    for(int x = 0; x < Map::getWidth(); x++)
    {
      if(isTile(x, y))
      {
        found = true;
        break;
      }
    }
    if(found)
      break;
  }

  /* Move up if no tiles in screen */
  if(!found)
  {
    total = - Timer::getPerSecond(NO_TILES_IN_SCREEN_SPEED);
  }


  for(;total != 0; total -= step)
  {
    step = abs_min((double)sgn(total), total);
    player.setY(player.getY() + step);

    /* Check if tiles crossed border */
      for(int x = 0; x < Map::getWidth(); x++)
      {
        if(isTile(x, (int)(player.getY() - BORDER_OFFSET)))
        {
          state = LEVEL_SCENE_FAILURE;
          erupt(ERUPTION_TIME_FAILURE);
          media::sfx::player_explosion.play();
        }
      }
  }
}


void Level::HandlePlayerAction()
{
//  media::sfx::player_explosion.play();
//  media::sfx::shot.play();

  if(Input::isButtonPressed(BUTTON_B))
  {
    FloatPoint position;

    position.setX(player.getTargetX());
    position.setY(player.getY() - BORDER_OFFSET);

    quadlist.push_back(new Quad(position));

    player.setState(PLAYER_SHOOTING);
    media::gfx::player::shooting.reset();
    media::sfx::shot.play();
  }


  if(player.getState() == PLAYER_SHOOTING && media::gfx::player::shooting.getLoopCount() > 0)
    player.setState(PLAYER_NORMAL);



  /* BOMB */
  if(Input::isButtonPressed(BUTTON_L) && player.getItemCount(ITEM_BOMB) > 0)
  {
    int fr, lr;

    fr = (int)player.getY();

    if(fr >= map_tile_range_y + 1)
      lr = fr - ((int)map_tile_range_y + 1);
    else
      lr = 0;


    for(int x = 0; x < Map::getWidth(); x++)
    {
      for(int y = lr; y <= fr; y++)
      {
        if(isTile(x, y))
          score += recursiveDestroyTiles(x, y);
      }
    }

    player.removeItem(ITEM_BOMB);

    media::sfx::item_bomb.play();
  }

  /* STOP */
  if(Input::isButtonPressed(BUTTON_Y) && player.getItemCount(ITEM_STOP) > 0)
  {
    stop_until = Timer::getTicks() + STOP_TIME;

    player.removeItem(ITEM_STOP);

    media::sfx::item_stop.play();
  }

  /* ROCKET */
  if(Input::isButtonPressed(BUTTON_X) && player.getItemCount(ITEM_ROCKET) > 0)
  {
    FloatPoint position;

    position.setX(player.getTargetX());
    position.setY(player.getY() - BORDER_OFFSET);

    rocketlist.push_back(new Rocket(position));

    player.removeItem(ITEM_ROCKET);

    media::sfx::item_rocket.play();
  }

  /* RAPIDFIRE */
  if(Input::isButtonPressed(BUTTON_A) && player.getItemCount(ITEM_RAPIDFIRE) > 0)
  {
    rapidfire_until = Timer::getTicks() + RAPIDFIRE_TIME;

    player.removeItem(ITEM_RAPIDFIRE);

    media::sfx::item_rapidfire.play();
  }
}


void Level::HandleMultiplier()
{
  multiplier.update();
}


void Level::HandleRockets()
{
  for(list<Rocket*>::iterator i = rocketlist.begin(); i != rocketlist.end();)
  {
    Rocket *rocket = *i;
    double step, total;
    bool erased = false;


    rocket->update();

    total = - Timer::getPerSecond(ROCKET_SPEED + speed);

    for(;total != 0; total -= step)
    {
      int x, y;

      step = abs_min((double)sgn(total), total);

      rocket->incY(step);


      /* Explode */
        x = rocket->getColumn();
        y = (int)(rocket->getY() - (double)(Rocket::getHeight()/2)/Map::getTileHeight());

        if(isTile(x, y))
        {
          int size;
          size = recursiveDestroyTiles(x, y);
          i = list_erase_and_delete(rocketlist, i);
          erased = true;

          AudioEffect(size);
          break;
        }


      /* Remove */
        if((rocket->getY() - camera.getY()) * Map::getTileHeight() + Rocket::getHeight()/2 < 0)
        {
          i = list_erase_and_delete(rocketlist, i);
          erased = true;
          break;
        }
    }

    if(!erased)
      i++;
  }
}


void Level::HandleItems()
{
  for(list<Item*>::iterator i = itemlist.begin(); i != itemlist.end();)
  {
    Item *item = *i;
    double step, total;
    bool erased = false;


    if(player.isItemFastcollect() && abs((int)player.getX() - (int)item->getX()) <= 1)
      total = Timer::getPerSecond(ITEM_FASTCOLLECT_SPEED);
    else
      total = Timer::getPerSecond(ITEM_SPEED);



    for(;total != 0; total -= step)
    {
      step = abs_min((double)sgn(total), total);
      item->incY(step);

      /* Remove */
        if(item->getY() - 0.5 > camera.getY() + MAP_RANGE_Y)
        {
          i = list_erase_and_delete(itemlist, i);
          erased = true;
          break;
        }

      /* Catch */
        if(fabs(item->getX() - player.getTargetX()) <= 1 && player.getY() - item->getY() < BORDER_OFFSET)
        {
          player.addItem(item->getType());

          i = list_erase_and_delete(itemlist, i);
          erased = true;
          break;
        }
    }

    if(!erased)
      i++;
  }
}


void Level::HandleParticles()
{
  IntRect livingarea;


  livingarea.setX((int)((camera.getPosition().getX() - ERUPTION_OFFSET_MAX) * Map::getTileWidth()));
  livingarea.setY((int)((camera.getPosition().getY() - ERUPTION_OFFSET_MAX) * Map::getTileHeight()));
  livingarea.setWidth((int)((Map::getWidth() + ERUPTION_OFFSET_MAX*2) * Map::getTileWidth()));
  livingarea.setHeight((int)(MAP_RANGE_Y + ERUPTION_OFFSET_MAX * Map::getTileHeight() * 2));

  particlemanager.setLivingArea(false, livingarea);

  particlemanager.update();
}


void Level::HandleMap()
{
  bool found;
  tmx::base::TileLayer *layer;


  layer = dynamic_cast<tmx::base::TileLayer*>(&Map::getLayer(0));

  if(handlemap_lastcheck.getX() != -1)
  {
    if(layer->getTile(handlemap_lastcheck.getX(), handlemap_lastcheck.getY()) != 0)
      return;
  }

  found = false;
  for(int y = 0; y < Map::getHeight() && !found; y++)
  {
    for(int x = 0; x < Map::getWidth(); x++)
    {
      if(layer->getTile(x, y) != 0)
      {
        handlemap_lastcheck.load(x, y);
        found = true;
        break;
      }
    }
  }

  if(!found)
  {
    state = LEVEL_SCENE_SUCCESS;
    player.setState(PLAYER_NORMAL);
  }

}


void Level::HandleCamera()
{
  FloatPoint position;

  position.setX(0);
  position.setY(player.getY() - map_tile_range_y);

  camera.setPosition(position);

}


void Level::DrawBackground()
{
  int pixelheight, pixelpassed, pixelrange;
  IntPoint center;
  IntVector rel;


  pixelheight = Map::getHeight() * Map::getTileHeight();
  pixelpassed = (int)(camera.getY() * Map::getTileHeight()) + MAP_RANGE_Y;
  pixelrange = background.getSize().getHeight() - MAP_RANGE_Y;

  center.setX(MAP_MIDDLE_X + (int)(camera.getX() * Map::getTileWidth()));
  center.setY(MAP_START_Y + background.getSize().getHeight()/2);

  rel.setY(-(int)(((double)pixelrange/pixelheight) * pixelpassed));


  background.draw(center + rel, ALIGN_BY_CENTER);
}


void Level::DrawMap()
{
  int pixelwidth, pixelheight;
  IntRect rect;
  IntPoint corner;


  pixelwidth = Map::getWidth() * Map::getTileWidth();
  pixelheight = Map::getHeight() * Map::getTileHeight();

  rect.setX(MAP_MIDDLE_X - pixelwidth/2);
  rect.setY(MAP_START_Y);
  rect.setWidth(pixelwidth);
  rect.setHeight(MAP_RANGE_Y);

  corner.setX((int)(camera.getX() * Map::getTileWidth()));
  corner.setY((int)(camera.getY() * Map::getTileHeight()));

  Map::draw(rect, corner);
}


void Level::DrawQuads()
{
  int pixelwidth;
  IntVector rel;

  pixelwidth = Map::getWidth() * Map::getTileWidth();

  rel.setX(Map::getTileWidth()/2  + MAP_MIDDLE_X - pixelwidth/2 - (int)(camera.getX() * Map::getTileWidth()));
  rel.setY(MAP_START_Y - (int)(camera.getY() * Map::getTileHeight()));

  for(list<Quad*>::iterator i = quadlist.begin(); i != quadlist.end(); i++)
  {
    Quad *quad = *i;
    IntPoint center;

    center.setX((int)(quad->getX() * Map::getTileWidth()));
    center.setY((int)(quad->getY() * Map::getTileHeight()));

    media::gfx::quad.draw(center + rel, ALIGN_BY_CENTER);
  }
}


void Level::DrawCursor()
{
  int pixelwidth;
  int fr, lr;
  IntPoint center;


  fr = (int)player.getY();

  if(fr >= map_tile_range_y + 1)
    lr = fr - ((int)map_tile_range_y);
  else
    lr = 0;

  pixelwidth = Map::getWidth() * Map::getTileWidth();

  for(int y = fr; y >= lr; y--)
  {
    if(isTile(player.getTargetX(), y))
    {
      center.setX((int)((player.getTargetX() * Map::getTileWidth()) + Map::getTileWidth()/2 + MAP_MIDDLE_X - pixelwidth/2 - camera.getX() * Map::getTileWidth()));
      center.setY((int)(MAP_START_Y - (camera.getY() - (y+1)) * Map::getTileHeight() + Map::getTileHeight()/2));
      break;
    }

    if(y == lr)
    {
      center.setX((int)((player.getTargetX() * Map::getTileWidth()) + Map::getTileWidth()/2 + MAP_MIDDLE_X - pixelwidth/2 - camera.getX() * Map::getTileWidth()));
      center.setY((int)(MAP_START_Y + Map::getTileHeight()/2 - camera.getOffset().getY() * Map::getTileWidth()));
      break;
    }
  }


  media::gfx::cursor.draw(center, ALIGN_BY_CENTER);
}


void Level::DrawPlayer()
{
  IntPoint center;

  center.setX((int)(MAP_MIDDLE_X + ((player.getX() - static_cast<double>(Map::getWidth())/2) * Map::getTileWidth()) + Map::getTileWidth()/2 - camera.getX() * Map::getTileWidth()));
  center.setY((int)((player.getY() - camera.getY() + PLAYER_OFFSET) * Map::getTileHeight()));

  switch(player.getState())
  {
    case PLAYER_NORMAL:   media::gfx::player::normal.draw(center, ALIGN_BY_CENTER);   break;
    case PLAYER_SHOOTING: media::gfx::player::shooting.draw(center, ALIGN_BY_CENTER); break;
  }

}


void Level::DrawRockets()
{
  int pixelwidth;
  IntVector rel;

  pixelwidth = Map::getWidth() * Map::getTileWidth();

  rel.setX(Map::getTileWidth()/2  + MAP_MIDDLE_X - pixelwidth/2 - (int)(camera.getX() * Map::getTileWidth()));
  rel.setY(MAP_START_Y - (int)(camera.getY() * Map::getTileHeight()));

  for(list<Rocket*>::iterator i = rocketlist.begin(); i != rocketlist.end(); i++)
  {
    Rocket *rocket = *i;
    IntPoint center;

    center.setX((int)(rocket->getX() * Map::getTileWidth()));
    center.setY((int)(rocket->getY() * Map::getTileHeight()));

    media::gfx::rocket.draw(center + rel, ALIGN_BY_CENTER);
  }
}


void Level::DrawItems()
{
  int pixelwidth;
  IntVector rel;

  pixelwidth = Map::getWidth() * Map::getTileWidth();

  rel.setX(Map::getTileWidth()/2  + MAP_MIDDLE_X - pixelwidth/2 - (int)(camera.getX() * Map::getTileWidth()));
  rel.setY(MAP_START_Y - (int)(camera.getY() * Map::getTileHeight()));

  for(list<Item*>::iterator i = itemlist.begin(); i != itemlist.end(); i++)
  {
    Item *item = *i;
    IntPoint center;

    center.setX((int)(item->getX() * Map::getTileWidth()));
    center.setY((int)(item->getY() * Map::getTileHeight()));

    media::gfx::item[item->getType()].draw(center + rel, ALIGN_BY_CENTER);
  }
}


void Level::DrawParticles()
{
  IntRect rect;
  IntPoint point;
  int pixelwidth;


  pixelwidth = Map::getWidth() * Map::getTileWidth();

  rect.setX(MAP_MIDDLE_X - GUI_VIEWPORT_WIDTH/2);
  rect.setY(GUI_VIEWPORT_Y);
  rect.setWidth(GUI_VIEWPORT_WIDTH);
  rect.setHeight(GUI_VIEWPORT_HEIGHT);

  point.setX((int)(camera.getX() * Map::getTileWidth()));
  point.setY((int)(camera.getY() * Map::getTileHeight()));

  particlemanager.draw(rect, point);
}


bool Level::isTile(int x, int y)
{
  tmx::base::TileLayer *layer = dynamic_cast<tmx::base::TileLayer*>(&Map::getLayer(0));

  if(x >= 0 && y >= 0 && x < (int)(Map::getWidth()) && y < (int)(Map::getHeight()))
    return layer->getTile(x, y) > 0;
  else
    return false;
}


int Level::getTile(int x, int y)
{
  tmx::base::TileLayer *layer = dynamic_cast<tmx::base::TileLayer*>(&Map::getLayer(0));
  return layer->getTile(x, y);
}


void Level::setTile(int x, int y, int id)
{
  tmx::base::TileLayer *layer = dynamic_cast<tmx::base::TileLayer*>(&Map::getLayer(0));
  layer->setTile(x, y, id);
}


int Level::recursiveDestroyTiles(int x, int y)
{
  int score;


  score = 0;

  if(isTile(x, y))
  {
    IntRect rect;
    MorphTile mt(getTile(x, y) - 1);

    setTile(x, y, 0);
    score++;

    /* Recursive removement */
      if(mt.isLeftOpen()   && isTile(x - 1, y)) score += recursiveDestroyTiles(x - 1, y);
      if(mt.isRightOpen()  && isTile(x + 1, y)) score += recursiveDestroyTiles(x + 1, y);
      if(mt.isTopOpen()    && isTile(x, y - 1)) score += recursiveDestroyTiles(x, y - 1);
      if(mt.isBottomOpen() && isTile(x, y + 1)) score += recursiveDestroyTiles(x, y + 1);


    /* Explosion effect */
      explodeTile(x, y);

    /* Eruption effect */
      erupt(ERUPTION_TIME_PER_TILE);
  }

  return score;
}


void Level::explodeTile(int x, int y)
{
  IntRect rect;

  rect.setX((int)(x * Map::getTileWidth()));
  rect.setY((int)(y * Map::getTileHeight()));
  rect.setWidth(Map::getTileWidth());
  rect.setHeight(Map::getTileHeight());

  particlemanager.genExplosionRect(rect, PARTICLES_PER_TILE, FloatRandom(PARTICLES_SPEED_MIN, PARTICLES_SPEED_MAX), IntRandom(PARTICLES_DURATION_MIN, PARTICLES_DURATION_MAX) , 0);
}


void Level::erupt(int time)
{
  if(eruption_until < Timer::getTicks())
    eruption_until = Timer::getTicks();

  eruption_until += time;

  if(eruption_until - Timer::getTicks() > ERUPTION_TIME_MAX)
    eruption_until = Timer::getTicks() + ERUPTION_TIME_MAX;
}


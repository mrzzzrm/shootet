#ifndef LEVEL_HPP
#define LEVEL_HPP

  #include <list>
  #include <cmath>

  #include "framework.hpp"


  #include "./config.hpp"
  #include "./media.hpp"
  #include "./Quad.hpp"
  #include "./MorphTile.hpp"
  #include "./Player.hpp"
  #include "./Rocket.hpp"
  #include "./Item.hpp"
  #include "./Camera.hpp"
  #include "./Multiplier.hpp"



  class Level: public tmx::render::Map, public util::Timer
  {
    public:

      Level();
      ~Level();

      /* Load/Clear */
        void load(const util::Path &path, LEVEL_DIFFICULTY difficulty, int number);
        void clear();


      /* Read properties */
          int getScore() const;
          double getSpeed() const;
          LEVEL_STATE getState() const;
          LEVEL_DIFFICULTY getDifficulty() const;
          int getNumber() const;

          Player &getPlayer();
          Multiplier &getMultiplier();
          Camera &getCamera();
          particle::ParticleManager &getParticleManager();


      /* Modify state */
        void setState(LEVEL_STATE state);


      /* Timer */
        void run();
        void pause();


      /* Loop */
        void update();
        void draw();


    private:

      /* Data */
        Camera camera;
        Player player;
        Multiplier multiplier;
        gfx::Image background;
        particle::ParticleManager particlemanager;

        std::list<Rocket*> rocketlist;
        std::list<Quad*> quadlist;
        std::list<Item*> itemlist;

        double speed;
        int score;

        int eruption_until;
        int desthalt_until;
        int stop_until;
        int rapidfire_until;

        geo::IntPoint handlemap_lastcheck;

        LEVEL_STATE state;

        LEVEL_DIFFICULTY difficulty;
        int number;

        double map_tile_range_y;


      /* Internals */
        /* Calculation Steps */
          void HandleEruption();
          void HandleQuads();
            bool HandleQuadMovement(Quad *quad);
            bool HandleQuadMapInteraction(Quad *quad);
              void AppendTile(int x, int y);
              geo::IntRect RemoveTileBlock(int stx, int sty);
              int ScoreEffect(const geo::IntRect &rect);
              void SpecialEffect(const geo::IntRect &rect, int score);
              void GraphicEffect(const geo::IntRect &rect, int score);
              void AudioEffect(int size);
              void AudioEffect(const geo::IntRect &rect);

          void HandlePlayer();
            void HandlePlayerMovement();
            void HandlePlayerAction();

          void HandleMultiplier();
          void HandleRockets();
          void HandleItems();
          void HandleParticles();

          void HandleMap();

          void HandleCamera();


        /* Draw steps */
          void DrawBackground();
          void DrawMap();
          void DrawQuads();
          void DrawCursor();
          void DrawPlayer();
          void DrawRockets();
          void DrawItems();
          void DrawParticles();


      /* Util */
        bool isTile(int x, int y);
        int getTile(int x, int y);
        void setTile(int x, int y, int id);

        int recursiveDestroyTiles(int x, int y);

        void explodeTile(int x, int y);

        void erupt(int time);



  };

#endif // LEVEL_HPP

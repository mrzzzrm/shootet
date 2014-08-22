#include "./TtfLabel.hpp"


using namespace std;
using namespace geo;
using namespace etc;
using namespace gfx;


namespace font
{
  TtfLabel::TtfLabel()
  {
    init();
  }


  TtfLabel::TtfLabel(const TtfFont *font, const std::string &text, const gfx::Color &color, TTF_RENDERMODE rendermode)
  {
    init();
    load(font, text, color, rendermode);
  }


  TtfLabel::TtfLabel(const TtfLabel &ttflabel)
  {
    init();
    load(ttflabel);
  }


  TtfLabel::~TtfLabel()
  {
    clear();
  }


  void TtfLabel::load(const TtfFont *font, const std::string &text, const gfx::Color &color, TTF_RENDERMODE rendermode)
  {
    setFont(font);
    setText(text);
    setColor(color);
    setRendermode(rendermode);

    renderIfChanged();
  }


  void TtfLabel::load(const TtfLabel &ttflabel)
  {
    if(&ttflabel == this)
      return;

    clear();

    current = ttflabel.current;
    requested = ttflabel.requested;

    if(ttflabel.image != NULL)
    image = new Image(*ttflabel.image);
  }


  void TtfLabel::clear()
  {
    if(image != NULL)
      delete image;

    current.text.clear();
    current.color.clear();
    requested.text.clear();
    requested.color.clear();

    init();
  }


  const TtfFont *TtfLabel::getFont() const
  {
    return current.font;
  }


  void TtfLabel::setFont(const TtfFont *font)
  {
    requested.font = font;
  }


  const gfx::Color &TtfLabel::getColor() const
  {
    return current.color;
  }


  void TtfLabel::setColor(const gfx::Color &color)
  {
    requested.color = color;
  }


  const std::string &TtfLabel::getText() const
  {
    return current.text;
  }


  void TtfLabel::setText(const std::string &text)
  {
    requested.text = text;
  }


  TTF_RENDERMODE TtfLabel::getRendermode() const
  {
    return current.rendermode;
  }


  void TtfLabel::setRendermode(TTF_RENDERMODE rendermode)
  {
    requested.rendermode = rendermode;
  }


  void TtfLabel::render()
  {
    if(image != NULL)
    {
      delete image;
      image = NULL;
    }

    if(requested.font == NULL)
      return;

    image = requested.font->render(requested.text, requested.color, requested.rendermode);

    current = requested;
  }


  void TtfLabel::renderIfChanged()
  {
    if
      (
       (current.font != requested.font && current.font != NULL && requested.font != NULL && *current.font != *requested.font) ||
       current.text != requested.text ||
       current.color != requested.color ||
       current.rendermode != requested.rendermode
      )
      render();
  }


  IntSize TtfLabel::getSize() const
  {
    if(image != NULL)
      return image->getSize();
    else
      return IntSize(0, 0);
  }


  void TtfLabel::draw(const IntPoint &pos, const Alignment &alignment, gfx::Image *image)
  {
    renderIfChanged();
    if(this->image != NULL)
    {
      this->image->draw(pos, alignment, IntRect(0, 0, -1, -1), image);
    }
  }


  void TtfLabel::drawConst(const IntPoint &pos, const Alignment &alignment, gfx::Image *image) const
  {
    if(this->image != NULL)
    {
      this->image->draw(pos, alignment, IntRect(0, 0, -1, -1), image);
    }
  }


  TtfLabel &TtfLabel::operator=(const TtfLabel &ttflabel)
  {
    load(ttflabel);
    return *this;
  }


  void TtfLabel::init()
  {
    current.font = NULL;
    current.rendermode = TTF_SOLID;
    requested.font = NULL;
    requested.rendermode = TTF_SOLID;

    image = NULL;
  }


}

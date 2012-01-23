#include "animations.h"

namespace visualizer
{
  void StartAnim::animate( const float& /* t */, AnimData * /* d */ )
  {
  }

  void DrawImage::animate( const float& /* t */, AnimData * /* d */ )
  {
    image &i = *m_image;
 
    i.renderer().setColor( Color( 1, 1, 1 ) );
    i.renderer().drawTexturedQuad( 0, 0, 1, 1, "bird" );

  }

  void DrawTextImage::animate( const float& /* t */, AnimData * /* d */ )
  {
    textImage &t = *m_textImage;
 
    t.renderer().setColor( Color( 1, 1, 1 ) );
    t.renderer().drawText( 0, 0, "mainFont", t.line );

  }

}

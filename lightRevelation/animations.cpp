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
    i.renderer().drawTexturedQuad( 0, 0, 1, 1, "visualExplosion" );

  }

}

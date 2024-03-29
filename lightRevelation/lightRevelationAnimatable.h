#ifndef LIGHT_REVELATION_ANIMATABLE_H
#define LIGHT_REVELATION_ANIMATABLE_H

#include "lightRevelationAnimatable.h"
#include "irenderer.h"

namespace visualizer
{
  struct image: public Animatable
  {
    image( IRenderer *render ) : Animatable( render )
    {}

    AnimData* getData()
    {
      return 0;
    }

  };

  struct textImage: public Animatable
  {
    textImage( IRenderer *render ) : Animatable( render )
    {}

    string line;
    string fontName;

    AnimData* getData()
    {
      return 0;
    }
  };

} // visualizer

#endif // LIGHT_REVELATION_ANIMATABLE_H

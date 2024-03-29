#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include "lightRevelationAnimatable.h"
#include "irenderer.h"

namespace visualizer
{

  struct StartAnim: public Anim
  {
    public:
      void animate( const float& t, AnimData *d );


      float controlDuration() const
      {
        return 0;
      }

      float totalDuration() const
      {
        return 0;
      }
  };

  struct DrawImage: public Anim
  {
    DrawImage( image *i )
    {
      m_image = i;
    }

    void animate( const float& t, AnimData* d);
    
    float controlDuration() const
    {
      return 0;
    }

    float totalDuration() const
    {
      return 0;
    }

    private:
      image* m_image;

  };

  struct DrawTextImage: public Anim
  {
    DrawTextImage( textImage *t )
    {
      m_textImage = t;
    }

    void animate( const float& t, AnimData* d);
    
    float controlDuration() const
    {
      return 0;
    }

    float totalDuration() const
    {
      return 0;
    }

    private:
      textImage* m_textImage;

  };
}

#endif // ANIMATION_H

#include "animations.h"

#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

namespace visualizer
{
  void StartAnim::animate( const float& t, AnimData *d, IGame* game )
  {
  } // StartAnim::animate()

  void DrawVirus::animate( const float& t, AnimData *d, IGame* game )
  {
    VirusData *vd = (VirusData*)d;
    virus &v = *m_virus;
    std:stringstream level;
    level << v.level;

    // Create the Display List's String ID
    stringstream displayListId;
    displayListId << "PlayerVirus-" << v.owner;
    
    // draw the virus's display list!
    game->renderer->push();
      game->renderer->translate(vd->x, vd->y);
      game->renderer->drawList(displayListId.str());
    game->renderer->pop();
    
    // draw the virus's level
    game->renderer->setColor( Color(1, 1, 1) );
    game->renderer->drawText( vd->x+0.2, vd->y+0.33, "mainFont", level.str(), 2.5 );
    
  } // DrawVirus::animate()

  void PushBoard::animate( const float& t, AnimData *d, IGame* game )
  {

    game->renderer->translate( 0, m_mb->offst );

  }

  void Appear::animate( const float& t, AnimData *d, IGame* game )
  {
    GeneralAnim* g = (GeneralAnim*)d;

    if( t < startTime )
    {
      g->alpha = 0;
    } else
    if( t > endTime )
    {
      g->alpha = 1;
    } else
    {
      g->alpha = easeOutBounce( t-startTime, 0, 1, endTime-startTime );
    } 

    g->alpha = 1;
     

  }

  void DrawBase::animate( const float& t, AnimData *d, IGame* game )
  {

    GeneralAnim *g = (GeneralAnim*) d;
    base &q = *m_base;

    float intensity;
    if( t < 0.5 )
    {
      intensity = easeOutCubic( t, .8, .2, 0.5 );
    } else
    {
      intensity = easeInCubic( t-.5, 1, -.2, 0.5 );
    }

    if( q.owner == 0 )
    {
      game->renderer->setColor( Color( 0.3f*intensity, 0, 0, 1 ) ); 
    }
    else if( q.owner == 1 )
    {
      game->renderer->setColor( Color( 0, 0, 0.3f*intensity, 1 ) );
    }
    
    game->renderer->drawQuad( q.x+.1, q.y+.1, .8, .8 );
    
    game->renderer->setColor( Color( 1,1,1 ) );
    game->renderer->drawTexturedQuad( q.x, q.y, 1, 1 , (q.owner ? "blue-server" : "red-server" ) );
    
  } // DrawBase::animate()

  void DrawTile::animate( const float& t, AnimData *d, IGame* game )
  {

    GeneralAnim *g = (GeneralAnim*) d;
    tile &q = *m_tile;
    
    // Player 1 owned Tile
    if( q.owner == 0 )
    {
      if( q.mainBlob )
      {
        game->renderer->setColor( Color( 0.65, 0, 0, 0.6 ) );
        game->renderer->drawQuad( q.x, q.y, 1, 1 );
        game->renderer->setColor( Color( 0.75, 0.75, 0.75 ) );
        stringstream s;
        s << "red-nodes-" << (int)q.x%4 << "," << (int)q.y%4;
        game->renderer->drawTexturedQuad( q.x, q.y, 1, 1 , s.str() );
      }
      else
      {
        game->renderer->setColor( Color( 0.3, 0, 0, 0.5 ) );
        game->renderer->drawQuad( q.x, q.y, 1, 1 );
      }
    }// PLayer 2 owned Tile
    else if( q.owner == 1 )
    {
      if( q.mainBlob )
      {
        game->renderer->setColor( Color( 0, 0, 0.65, 0.6 ) );
        game->renderer->drawQuad( q.x, q.y, 1, 1 );
        game->renderer->setColor( Color( 0.75, 0.75, 0.75 ) );
        stringstream s;
        s << "blue-nodes-" << (int)q.x%4 << "," << (int)q.y%4;
        game->renderer->drawTexturedQuad( q.x, q.y, 1, 1 , s.str() );
      }
      else
      {
        game->renderer->setColor( Color( 0, 0, 0.3, 0.5 ) );
        game->renderer->drawQuad( q.x, q.y, 1, 1 );
      }
    }
    // Nobody owns this tile
    else if( q.owner == 2 )
    {
      game->renderer->setColor( Color( 0.1, 0.1, 0.1, 0.0 ) );
      game->renderer->drawQuad( q.x, q.y, 1, 1 );
    }
    // Wall Tile
    else if( q.owner == 3 )
    {
      game->renderer->setColor( Color( 1.0, 1.0, 1.0 ) );
      srand(40 * q.x + q.y);
      stringstream s;
      s << "wall-" << rand()%5;
      game->renderer->drawTexturedQuad( q.x, q.y, 1, 1 , s.str() );
    }

  } // DrawTile::animate()

  void CrashLeft::animate( const float& t, AnimData *d, IGame* game )
  {
    VirusData *v = (VirusData*)d;
    float offset = 0.5f * (m_dampner);
    if( t > startTime && t < endTime )
    {
      if( t < (startTime+endTime)/2 )
      {
        v->x = easeOutCubic( t-startTime, v->x, -offset, (endTime-startTime)/2 );
      }
      else
      {
        v->x = easeInCubic( t-((startTime+endTime)/2), v->x-offset, offset, (endTime-startTime)/2 );
      }

    } 

  }

  void CrashRight::animate( const float& t, AnimData *d, IGame* game )
  {
    VirusData *v = (VirusData*)d;
    float offset = 0.5f * (m_dampner);
    if( t > startTime && t < endTime )
    {
      if( t < (startTime+endTime)/2 )
      {
        v->x = easeOutCubic( t-startTime, v->x, offset, (endTime-startTime)/2 );
      }
      else
      {
        v->x = easeInCubic( t-((startTime+endTime)/2), v->x+offset, -offset, (endTime-startTime)/2 );
      }

    } 

  }

  void CrashUp::animate( const float& t, AnimData *d, IGame* game )
  {
    VirusData *v = (VirusData*)d;
    float offset = 0.5f * (m_dampner);
    if( t > startTime && t < endTime )
    {
      if( t < (startTime+endTime)/2 )
      {
        v->y = easeOutCubic( t-startTime, v->y, -offset, (endTime-startTime)/2 );
      }
      else
      {
        v->y = easeInCubic( t-((startTime+endTime)/2), v->y-offset, offset, (endTime-startTime)/2 );
      }

    } 

  }

  void CrashDown::animate( const float& t, AnimData *d, IGame* game )
  {
    VirusData *v = (VirusData*)d;

    float offset = 0.5f * (m_dampner);
    if( t > startTime && t < endTime )
    {
      if( t < (startTime+endTime)/2 )
      {
        v->y = easeOutCubic( t-startTime, v->y, offset, (endTime-startTime)/2 );
      }
      else
      {
        v->y = easeInCubic( t-((startTime+endTime)/2), v->y+offset, -offset, (endTime-startTime)/2 );
      }

    } 

  }



  void LeftAnim::animate( const float& t, AnimData *d, IGame* game )
  {
    VirusData *v = (VirusData*)d;
    if( t > startTime && t < endTime )
    {
      v->x = easeInOutCubic( t-startTime, v->x, -1, endTime-startTime );
    } else if ( t >= endTime )
    {
      v->x--;
    }
  } // LeftAnim::animate()

  void RightAnim::animate( const float& t, AnimData *d, IGame* game )
  {
    VirusData *v = (VirusData*)d;
    if( t > startTime && t < endTime )
    {
      v->x = easeInOutCubic( t-startTime, v->x, 1, endTime-startTime );
    } else if( t >= endTime )
    {
      v->x++;
    }
  } // RightAnim::animate() 

  void UpAnim::animate( const float& t, AnimData *d, IGame* game )
  {
    VirusData *v = (VirusData*)d;
    if( t > startTime && t < endTime )
    {
      v->y = easeInOutCubic( t-startTime, v->y, 1, endTime-startTime );
    } else if( t >= endTime )
    {
      v->y++;
    }
  } // UpAnim::animate()

  void DownAnim::animate(const float& t, AnimData *d, IGame* game )
  {
    // I think this is actually up
    VirusData *v = (VirusData*)d;
    if( t > startTime && t < endTime )
    {
      v->y = easeInOutCubic( t-startTime, v->y, -1, endTime-startTime );
    } else if( t >= endTime )
    {
      v->y--;
    }
  } // DownAnim::animate()


  void DrawBackground::animate( const float& t, AnimData *d, IGame* game )
  {
    game->renderer->drawList( "backgroundDraw" );

  } // DrawBackground::animate
  
  void DrawGrid::animate( const float& t, AnimData *d, IGame* game )
  {
    for(int x = 0; x < m_grid->mapWidth; x++)
    {
      game->renderer->setColor( Color( 0.2, 0.2, 0.2, 0.5 ) );
      game->renderer->drawLine(x, 0, x, m_grid->mapHeight, 1.0);
    }
    
    for(int y = 0; y < m_grid->mapHeight; y++)
    {
      game->renderer->setColor( Color( 0.2, 0.2, 0.2, 0.5 ) );
      game->renderer->drawLine(0, y, m_grid->mapWidth, y, 1.0);
    }
  } // DrawGrid::animate
  
  void UpCollide::animate(const float& t, AnimData *d, IGame* game)
  {
    VirusData *v = (VirusData*)d;
    float mid = (startTime+endTime)/2;
    
      if(t > endTime)
      {
      }
      else if (t<mid)
      {
        v->y = easeInCubic(startTime,v->y,-1,mid-startTime);
      } 
      else if (t>=mid)
      {
        v->y = easeOutCubic(mid,v->y-1,+1,endTime-mid);
      }
  } // UpCollide::animate()
  
  void DownCollide::animate(const float& t, AnimData *d, IGame* game)
  {
    VirusData *v = (VirusData*)d;
    float mid = (startTime+endTime)/2;
    if(t > endTime)
    {
    }
    else if(t<mid)
    {
      v->y = easeInCubic(startTime,v->y,+1,mid-startTime);
    }
    else if (t>=mid)
    {
      v->y = easeOutCubic(mid,v->y+1,-1,endTime-mid);
    }
  }

  void LeftCollide::animate(const float& t, AnimData *d, IGame* game)
  {
    VirusData *v = (VirusData*)d;
    float mid = (startTime+endTime)/2;
    if(t > endTime)
    {
    }
    else if(t<mid)
    {
      v->x = easeInCubic(startTime,v->x,-1,mid-startTime);
    }
    else if (t>=mid)
    {
       v->x = easeOutCubic(mid,v->x-1,+1,endTime-mid);
    }
  }
  
  void RightCollide::animate(const float& t, AnimData *d, IGame* game)
  {
    VirusData *v = (VirusData*)d;
    float mid = (startTime + endTime)/2;                          
    
    if(t>endTime)
    {
    }
    else if (t<mid)
    {
      v->x = easeInCubic(startTime,v->x,+1,mid-startTime);
    }
    else if (t>=mid)
    {
      v->x = easeOutCubic(mid,v->x+1,-1,endTime-mid);
    }
  }

  void DrawScore::animate( const float& t, AnimData* d, IGame *game )
  {
    stringstream ss;
    ss << ":" << m_sb->score;
    
    game->renderer->translate(0, -2.5);
    IRenderer::Alignment a = IRenderer::Left;
    Color team = Color( 1, 0, 0 );
    Color darkTeam = Color (0.6, 0, 0);
    
    Color red  = Color (1, 0, 0);
    Color blue = Color (0, 0, 1);
    Color darkRed  = Color (0.5, 0, 0);
    Color darkBlue = Color (0, 0, 0.5);
    Color neutral = Color ( 0.667, 0.669, 0.667);
    
    double startX = 0;
    double endX   = m_sb->mapWidth;
    double xTextOffset = 1.5;
    double xBottomInfoOffset = 2.875;
    double xVirusOffset = -0.75;
    double scoreOffset = 12.75;
    string scoreFileName = "scoreboard-bytedollar-red";
    ScoreData *sd = (ScoreData*)d;
    
    if( m_sb->player == 1 )
    {
      a = IRenderer::Right;
      team = Color( 0, 1, 1 );
      darkTeam = Color( 0, 0.6, 0.6 );
      scoreOffset = 23.75;
      scoreFileName = "scoreboard-bytedollar-blue";
      startX = m_sb->mapWidth * (sd->blueOffset + sd->drawnOffset);
      endX   =  m_sb->mapWidth * (1 - (sd->blueOffset + sd->drawnOffset));
      xTextOffset = -2.1;
      xVirusOffset = -1.25;     
      xBottomInfoOffset = 26.8;
    }
    else
    {
      game->renderer->drawList( "drawHeader" );

    }
    
    // set the team's color and then draw thier team's name
    game->renderer->setColor( team ); 
    float textSize = 4.5;
    if(m_sb->teamName.length() > 17)
        textSize = 4.5 * (17 / ((float)m_sb->teamName.length()));
    game->renderer->drawText( m_sb->x + xTextOffset, m_sb->y + (textSize - ((float)textSize * 1.045f)) , "mainFont", m_sb->teamName, textSize, a );

    // cycles
    stringstream bottomInfo;
    bottomInfo << "scoreboard-cycles-" << (m_sb->player ? "blue" : "red");
    game->renderer->drawTexturedQuad(scoreOffset, m_sb->y, 1, 1, bottomInfo.str());
    bottomInfo.str("");
    bottomInfo.clear();
    bottomInfo << ":" << m_sb->cycles;
    game->renderer->drawText(scoreOffset + 0.76, m_sb->y - 0.1, "mainFont", bottomInfo.str(), 4.5);
    
    //draw their score too
    game->renderer->drawTexturedQuad(scoreOffset + (m_sb->player ? -3.4 : 4), m_sb->y, 1, 1, scoreFileName);
    game->renderer->drawText( scoreOffset + (m_sb->player ? -3 : 4.4), m_sb->y - 0.1, "mainFont", ss.str(), 4.5 );

    // draw the virus
    // Create the Display List's String ID
    stringstream displayListId;
    displayListId << "PlayerVirus-" << m_sb->player;
    
    // draw the virus's display list!
    game->renderer->push();
    game->renderer->translate(m_sb->x + xVirusOffset, m_sb->y - 0.125);
    game->renderer->scale(2.0, 2.0);
    game->renderer->drawList(displayListId.str());
    game->renderer->pop();

    if( m_sb->player == 0 )
    {
      float allTiles = m_sb->unconnectedTiles + m_sb->connectedTiles + m_sb->neutralTiles + m_sb->enemyUnconnectedTiles + m_sb->enemyConnectedTiles;
      
      float redConnectedTilesWidth = m_sb->mapWidth * ((float)m_sb->connectedTiles / allTiles);
      float redUnconnectedTilesWidth = m_sb->mapWidth * ((float)m_sb->unconnectedTiles / allTiles);
      float neutralTilesWidth = m_sb->mapWidth * ((float)m_sb->neutralTiles / allTiles);
      float blueConnectedTilesWidth = m_sb->mapWidth * ((float)m_sb->enemyConnectedTiles / allTiles);
      float blueUnconnectedTilesWidth = m_sb->mapWidth * ((float)m_sb->enemyUnconnectedTiles / allTiles);
      
      // draw the red team connected bar
      game->renderer->setColor( red );
      game->renderer->drawQuad(0, m_sb->y + 2, redConnectedTilesWidth, 0.25);
      
      // draw the red team unconnected bar
      game->renderer->setColor( darkRed );
      game->renderer->drawQuad(redConnectedTilesWidth, m_sb->y + 2, redUnconnectedTilesWidth, 0.25);
      
      // draw the neutral bar
      game->renderer->setColor( neutral );
      game->renderer->drawQuad(redConnectedTilesWidth + redUnconnectedTilesWidth, m_sb->y + 2, neutralTilesWidth, 0.25);
      
      // draw the blue team connected bar
      game->renderer->setColor( darkBlue );
      game->renderer->drawQuad(redConnectedTilesWidth + redUnconnectedTilesWidth + neutralTilesWidth, m_sb->y + 2, blueUnconnectedTilesWidth, 0.25);
      
      // draw the blue team unconnected bar
      game->renderer->setColor( blue );
      game->renderer->drawQuad(redConnectedTilesWidth + redUnconnectedTilesWidth + neutralTilesWidth + blueUnconnectedTilesWidth, m_sb->y + 2, blueConnectedTilesWidth, 0.25);
      
      // draw the center marker
      game->renderer->setColor( Color( 0.333, 0.33, 0.333) );
      game->renderer->drawLine(m_sb->mapWidth/2, m_sb->y + 1.75, m_sb->mapWidth/2, m_sb->y + 2.25, 2);
    }
    
    game->renderer->translate(0, 2.5);
  }
  
  void ScoreAnim::animate( const float& t, AnimData *d, IGame* game )
  {
    ScoreData *s = (ScoreData*)d;
    
    double oldBlueOffset = 1 - (double)oldBluScore / (double)(oldBluScore + oldRedScore);
    double curBlueOffset = 1 - (double)currentBluScore / (double)(currentBluScore + currentRedScore);
    double blueOffset = curBlueOffset - oldBlueOffset;
    
    if( t > startTime && t < endTime/2 )
    {
      s->drawnOffset = blueOffset * (t * 2);
      s->blueOffset = oldBlueOffset;
    } else if( t >= endTime/2 )
    {
      s->drawnOffset = 0;
      s->blueOffset = curBlueOffset;
    }
    
  } // ScoreAnim::animate() 

  void DrawTalk::animate( const float& t, AnimData *d, IGame* game )
  {
    IRenderer::Alignment align = IRenderer::Left;
    float xPos = 2.5;
    
    if( m_talker->player == 0 )
    {
      game->renderer->setColor( Color( 1, 0, 0 ) );
    }
    else
    {
      game->renderer->setColor( Color( 0, 1, 1 ) );
      align = IRenderer::Right;
      xPos = 37.5;
    }

    game->renderer->drawText( xPos, -1.25, "mainFont", m_talker->message, 2.75, align );

  } // DrawTalk::animate()
  
  void DrawArenaWinner::animate( const float& t, AnimData *d, IGame* game )
  {
    if( firstRun )
    {
      game->timeManager->setSpeed(m_winSpeed);
      game->timeManager->setTurnPercent( 0 );
      firstRun = false;

    }

    IRenderer::Alignment align = IRenderer::Center;
    stringstream ss;

    float alpha = 1;

    if( t < 0.3 )
    {
      alpha = easeInCubic( t, 0, 1, 0.3 );

    }
    
    Color teamColor = m_aw->winnersIndex ? Color(0,0,0.7, alpha): Color(0.7,0,0, alpha);
    Color blackColor = Color(0.12,0.12,0.12, alpha);
    game->renderer->setColor( Color(1, 1, 1, alpha*0.7 ) );
    game->renderer->drawQuad(0, 0, 40, 20);
    
    // Draw the Winner's Name
    game->renderer->setColor( blackColor );
    game->renderer->drawText( m_aw->mapWidth/2, m_aw->mapHeight/2 - 9, "mainFont", "Winner:", 4, align );
    game->renderer->setColor( teamColor );
    game->renderer->drawText( m_aw->mapWidth/2, m_aw->mapHeight/2 - 8, "mainFont", m_aw->winnersName, 7, align );
    
    // Draw tyhe winner's Virus
    stringstream displayListId;
    displayListId << "PlayerVirus-" << m_aw->winnersIndex;
    game->renderer->push();
    game->renderer->translate(m_aw->mapWidth/2 - 6.0, m_aw->mapHeight/2 -6.0);
    game->renderer->scale(12.0, 12.0);
    game->renderer->drawList(displayListId.str());
    game->renderer->pop();
    
    // easter egg: draw wooly willy
    if(m_aw->woolyTime)
      game->renderer->drawTexturedQuad( m_aw->mapWidth/2 - 6.0, m_aw->mapHeight/2 -6.0, 12, 12, "wooly-willy" );
    
    // Draw the Winning reason
    game->renderer->setColor( blackColor );
    game->renderer->drawText( m_aw->mapWidth/2, m_aw->mapHeight/2 + 7, "mainFont", m_aw->winningReason, 4.5, align );
    
  } // DrawArenaWinner::animate()
  
  void ArenaWinnerAnim::animate( const float& t, AnimData *d, IGame* game )
  {
    ArenaWinnerData *a = (ArenaWinnerData*)d;
    
  } // ScoreAnim::animate() 

} // visualizer



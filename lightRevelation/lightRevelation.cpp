#include "lightRevelation.h"
#include "lightRevelationAnimatable.h"
#include "frame.h"
#include "animations.h"

namespace visualizer
{

  LightRevelation::LightRevelation()
  {
  } // LightRevelation::LightRevelation()

  LightRevelation::~LightRevelation()
  {
  } // LightRevelation::~LightRevelation()

  // used to figure out whether the game log is a LightRevelation one
  // or not
  LogRegex LightRevelation::logFileInfo()
  {
    // Regular expression used for the checking
    LogRegex lr;
    lr.regex = "\x89PNG";
    // Number of characters at the beginning of gameLogFile to check
    // with lr before giving up
    lr.startSize = 40;
    lr.giveFilename = true;

    return lr;
  } // LogRegex LightRevelation::logFileInfo()

  void LightRevelation::loadGamelog( std::string gameLogFile )
  {
    cout << gameLogFile << endl;
    cout << "Load Bloom Gamelog" << endl;

    renderer->setCamera( 0, 0, 1024, 1024 );
    renderer->setUnitSize( 1024, 1024 );
    resourceManager->loadTexture( gameLogFile, "visualExplosion" );
    Frame turn;
    image *i = new image( renderer );
    i->addKeyFrame( new StartAnim );
    i->addKeyFrame( new DrawImage( i ) );
    turn.addAnimatable( i );
    addFrame( turn );

    timeManager->setNumTurns( 1 );
    animationEngine->registerFrameContainer( this );
    timeManager->play();					//really don't need this beeteedubs

  } // LightRevelation::loadGamelog()



} // visualizer

Q_EXPORT_PLUGIN2( lightRevelation, visualizer::LightRevelation );

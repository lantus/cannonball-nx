/***************************************************************************
    XML Configuration File Handling.

    Load Settings.
    Load & Save Hi-Scores.

    Copyright Chris White.
    See license.txt for more details.
***************************************************************************/

// see: http://www.boost.org/doc/libs/1_52_0/doc/html/boost_propertytree/tutorial.html
 
#include <iostream>

#include "main.hpp"
#include "config.hpp"
#include "globals.hpp"
#include "setup.hpp"
#include "../utils.hpp"

#include "engine/ohiscore.hpp"
#include "engine/audio/osoundint.hpp"

 

Config config;

Config::Config(void)
{

}


Config::~Config(void)
{
}

void Config::init()
{

// ------------------------------------------------------------------------
    // Menu Settings
    // ------------------------------------------------------------------------

    menu.enabled           = 0;
    menu.road_scroll_speed = 50;

    // ------------------------------------------------------------------------
    // Video Settings
    // ------------------------------------------------------------------------
   
    video.mode       =  video_settings_t::MODE_FULL;
    video.scale      = 0;
    video.scanlines  = 0;
    video.fps        = 0;
    video.fps_count  = 1;
    video.widescreen = 0;
    video.hires      = 0;
    video.filtering  = 0;
          
    set_fps(video.fps);

    // ------------------------------------------------------------------------
    // Sound Settings
    // ------------------------------------------------------------------------
    sound.enabled     = 0;
    sound.advertise   = 0;
    sound.preview     = 1;
    sound.fix_samples = 0;

    // Custom Music
    for (int i = 0; i < 4; i++)
    {
        
      
        sound.custom_music[i].enabled = 0;
        
    }
    
    controls.gear          = 0;
    controls.steer_speed   = 3;
    controls.pedal_speed   = 4;
    controls.keyconfig[0]  = 273;
    controls.keyconfig[1]  = 274;
    controls.keyconfig[2]  = 276;
    controls.keyconfig[3]  = 275;
    controls.keyconfig[4]  = 122;
    controls.keyconfig[5]  = 120;
    controls.keyconfig[6]  = 32;
    controls.keyconfig[7]  = 32;
    controls.keyconfig[8]  = 49;
    controls.keyconfig[9]  = 53;
    controls.keyconfig[10] = 286;
    controls.keyconfig[11] = 304;
    controls.padconfig[0]  = 0;
    controls.padconfig[1]  = 1;
    controls.padconfig[2]  = 2;
    controls.padconfig[3]  = 2;
    controls.padconfig[4]  = 3;
    controls.padconfig[5]  = 4;
    controls.padconfig[6]  = 5;
    controls.padconfig[7]  = 6;
    controls.analog        = 0;
    controls.pad_id        = 0;
    controls.axis[0]       = 0;
    controls.axis[1]       = 2;
    controls.axis[2]       = 3;
    controls.asettings[0]  = 75;
    controls.asettings[1]  = 0;
    controls.asettings[2]  = 0;
    
 

    // ------------------------------------------------------------------------
    // CannonBoard Settings
    // ------------------------------------------------------------------------
    cannonboard.enabled = 0;
    cannonboard.port    = "80";
    cannonboard.baud    = 1212;
    cannonboard.debug   = 0;
    cannonboard.cabinet = 0;

 

    // ------------------------------------------------------------------------
    // Engine Settings
    // ------------------------------------------------------------------------

    engine.dip_time      = 0;
    engine.dip_traffic   = 1;
    
    engine.freeze_timer    = engine.dip_time == 4;
    engine.disable_traffic = engine.dip_traffic == 4;
    engine.dip_time    &= 3;
    engine.dip_traffic &= 3;

    engine.freeplay      = 0;
    engine.jap           = 0;
    engine.prototype     = 0;
    
    // Additional Level Objects
    engine.level_objects   = 0;
    engine.randomgen       = 0;
    engine.fix_bugs_backup = 0;
    engine.fix_bugs        = 0;
    engine.fix_timer       = 0;
    engine.layout_debug    = 0;
    engine.new_attract     = 0;

    // ------------------------------------------------------------------------
    // Time Trial Mode
    // ------------------------------------------------------------------------

    ttrial.laps    = 5;
    ttrial.traffic = 3;

    cont_traffic   = 3;

}

 

void Config::load(const std::string &filename)
{
    
}

bool Config::save(const std::string &filename)
{
    
    return true;
}

void Config::load_scores(const std::string &filename)
{
    // Create empty property tree object
  
}

void Config::save_scores(const std::string &filename)
{
    
}

void Config::load_tiletrial_scores()
{
 
}

void Config::save_tiletrial_scores()
{
    
}

bool Config::clear_scores()
{
     
    return 0;
}

void Config::set_fps(int fps)
{
    video.fps = fps;
    // Set core FPS to 30fps or 60fps
    this->fps = video.fps == 0 ? 30 : 60;
    
    // Original game ticks sprites at 30fps but background scroll at 60fps
    tick_fps  = video.fps < 2 ? 30 : 60;

    cannonball::frame_ms = 1000.0 / this->fps;

    #ifdef COMPILE_SOUND_CODE
    if (config.sound.enabled)
        cannonball::audio.stop_audio();
    osoundint.init();
    if (config.sound.enabled)
        cannonball::audio.start_audio();
    #endif
}

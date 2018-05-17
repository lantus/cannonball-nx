/***************************************************************************
    Front End Menu System.

    This file is part of Cannonball. 
    Copyright Chris White.
    See license.txt for more details.
***************************************************************************/

// Boost string prediction
 

#include "main.hpp"
#include "menu.hpp"
#include "setup.hpp"
#include "../utils.hpp"
#include "../cannonboard/interface.hpp"

#include "engine/ohud.hpp"
#include "engine/oinputs.hpp"
#include "engine/osprites.hpp"
#include "engine/ologo.hpp"
#include "engine/opalette.hpp"
#include "engine/otiles.hpp"

#include "engine/oinitengine.hpp"
#include "engine/oroad.hpp"

#include "frontend/cabdiag.hpp"
#include "frontend/ttrial.hpp"

#include "engine/audio/osoundint.hpp"
#include "engine/audio/osound.hpp"

// Logo Y Position
const static int16_t LOGO_Y = -60;

// Columns and rows available
const static uint16_t COLS = 40;
const static uint16_t ROWS = 28;

// Horizon Destination Position
const static uint16_t HORIZON_DEST = 0x3A0;

// ------------------------------------------------------------------------------------------------
// Text Labels for menus
// ------------------------------------------------------------------------------------------------

// Back Labels
const static char* ENTRY_BACK       = "BACK";

// Main Menu
const static char* ENTRY_PLAYGAME   = "PLAY GAME";
const static char* ENTRY_GAMEMODES  = "GAME MODES";
const static char* ENTRY_SETTINGS   = "SETTINGS";
const static char* ENTRY_ABOUT      = "ABOUT";
const static char* ENTRY_EXIT       = "EXIT";

// Game Modes Menu
const static char* ENTRY_ENHANCED   = "SET ENHANCED MODE";
const static char* ENTRY_ORIGINAL   = "SET ORIGINAL MODE";
const static char* ENTRY_CONT       = "CONTINUOUS MODE";
const static char* ENTRY_TIMETRIAL  = "TIME TRIAL MODE";

// Time Trial Menu
const static char* ENTRY_START      =  "START TIME TRIAL";
const static char* ENTRY_LAPS       =  "NO OF LAPS ";

// Continuous Menu
const static char* ENTRY_START_CONT = "START CONTINUOUS MODE";

// Settings Menu
const static char* ENTRY_VIDEO      = "VIDEO";
const static char* ENTRY_SOUND      = "SOUND";
const static char* ENTRY_CONTROLS   = "CONTROLS";
const static char* ENTRY_CANNONBOARD= "CANNONBOARD";
const static char* ENTRY_ENGINE     = "GAME ENGINE";
const static char* ENTRY_SCORES     = "CLEAR HISCORES";
const static char* ENTRY_SAVE       = "SAVE AND RETURN";

// CannonBoard Menu
const static char* ENTRY_C_INTERFACE= "INTERFACE DIAGNOSTICS";
const static char* ENTRY_C_INPUTS   = "INPUT TEST";
const static char* ENTRY_C_OUTPUTS  = "OUTPUT TEST";
const static char* ENTRY_C_CRT      = "CRT TEST";

// Video Menu
const static char* ENTRY_FPS        = "FRAME RATE ";
const static char* ENTRY_FULLSCREEN = "FULL SCREEN ";
const static char* ENTRY_WIDESCREEN = "WIDESCREEN ";
const static char* ENTRY_HIRES      = "HIRES ";
const static char* ENTRY_SCALE      = "WINDOW SCALE ";
const static char* ENTRY_SCANLINES  = "SCANLINES ";

// Sound Menu
const static char* ENTRY_MUTE       = "SOUND ";
const static char* ENTRY_BGM        = "BGM VOL ";
const static char* ENTRY_SFX        = "SFX VOL ";
const static char* ENTRY_ADVERTISE  = "ADVERTISE SOUND ";
const static char* ENTRY_PREVIEWSND = "PREVIEW MUSIC ";
const static char* ENTRY_FIXSAMPLES = "FIX SAMPLES ";
const static char* ENTRY_MUSICTEST  = "MUSIC TEST";

// Controls Menu
const static char* ENTRY_GEAR       = "GEAR ";
const static char* ENTRY_ANALOG     = "ANALOG ";
const static char* ENTRY_REDEFJOY   = "REDEFINE GAMEPAD";
const static char* ENTRY_REDEFKEY   = "REDEFINE KEYS";
const static char* ENTRY_DSTEER     = "DIGITAL STEER SPEED ";
const static char* ENTRY_DPEDAL     = "DIGITAL PEDAL SPEED ";

// Game Engine Menu
const static char* ENTRY_TRACKS     = "TRACKS ";
const static char* ENTRY_TIME       = "TIME ";
const static char* ENTRY_TRAFFIC    = "TRAFFIC ";
const static char* ENTRY_OBJECTS    = "OBJECTS ";
const static char* ENTRY_PROTOTYPE  = "PROTOTYPE STAGE 1 ";
const static char* ENTRY_ATTRACT    = "NEW ATTRACT ";

// Music Test Menu
const static char* ENTRY_MUSIC1     = "MAGICAL SOUND SHOWER";
const static char* ENTRY_MUSIC2     = "PASSING BREEZE";
const static char* ENTRY_MUSIC3     = "SPLASH WAVE";
const static char* ENTRY_MUSIC4     = "LAST WAVE";

Menu::Menu(Interface* cannonboard)
{
    this->cannonboard = cannonboard;
    cabdiag = new CabDiag(cannonboard);
    ttrial  = new TTrial(config.ttrial.best_times);
}


Menu::~Menu(void)
{
    delete cabdiag;
    delete ttrial;
}

void Menu::populate()
{
    // Create Menus
    menu_main.push_back(ENTRY_PLAYGAME);
    menu_main.push_back(ENTRY_GAMEMODES);
    menu_main.push_back(ENTRY_SETTINGS);
    menu_main.push_back(ENTRY_ABOUT);
    menu_main.push_back(ENTRY_EXIT);

    menu_gamemodes.push_back(ENTRY_ENHANCED);
    menu_gamemodes.push_back(ENTRY_ORIGINAL);
    menu_gamemodes.push_back(ENTRY_CONT);
    menu_gamemodes.push_back(ENTRY_TIMETRIAL);
    menu_gamemodes.push_back(ENTRY_BACK);

    menu_cont.push_back(ENTRY_START_CONT);
    menu_cont.push_back(ENTRY_TRAFFIC);
    menu_cont.push_back(ENTRY_BACK);

    menu_timetrial.push_back(ENTRY_START);
    menu_timetrial.push_back(ENTRY_LAPS);
    menu_timetrial.push_back(ENTRY_TRAFFIC);
    menu_timetrial.push_back(ENTRY_BACK);

    menu_settings.push_back(ENTRY_VIDEO);
    #ifdef COMPILE_SOUND_CODE
    menu_settings.push_back(ENTRY_SOUND);
    #endif
    menu_settings.push_back(ENTRY_CONTROLS);
    if (config.cannonboard.enabled)
        menu_settings.push_back(ENTRY_CANNONBOARD);
    menu_settings.push_back(ENTRY_ENGINE);
    menu_settings.push_back(ENTRY_SCORES);
    menu_settings.push_back(ENTRY_SAVE);

    menu_cannonboard.push_back(ENTRY_C_INTERFACE);
    menu_cannonboard.push_back(ENTRY_C_INPUTS);
    menu_cannonboard.push_back(ENTRY_C_OUTPUTS);
    menu_cannonboard.push_back(ENTRY_C_CRT);
    menu_cannonboard.push_back(ENTRY_BACK);

    menu_video.push_back(ENTRY_FPS);
    menu_video.push_back(ENTRY_FULLSCREEN);
    menu_video.push_back(ENTRY_WIDESCREEN);
    menu_video.push_back(ENTRY_HIRES);
    menu_video.push_back(ENTRY_SCALE);
    menu_video.push_back(ENTRY_SCANLINES);
    menu_video.push_back(ENTRY_BACK);

    menu_sound.push_back(ENTRY_MUTE);
    //menu_sound.push_back(ENTRY_BGM);
    //menu_sound.push_back(ENTRY_SFX);
    menu_sound.push_back(ENTRY_ADVERTISE);
    menu_sound.push_back(ENTRY_PREVIEWSND);
    menu_sound.push_back(ENTRY_FIXSAMPLES);
    menu_sound.push_back(ENTRY_MUSICTEST);
    menu_sound.push_back(ENTRY_BACK);

    menu_controls.push_back(ENTRY_GEAR);
    if (input.gamepad) menu_controls.push_back(ENTRY_ANALOG);
    menu_controls.push_back(ENTRY_REDEFKEY);
    if (input.gamepad) menu_controls.push_back(ENTRY_REDEFJOY);
    menu_controls.push_back(ENTRY_DSTEER);
    menu_controls.push_back(ENTRY_DPEDAL);
    menu_controls.push_back(ENTRY_BACK);

    menu_engine.push_back(ENTRY_TRACKS);
    menu_engine.push_back(ENTRY_TIME);
    menu_engine.push_back(ENTRY_TRAFFIC);
    menu_engine.push_back(ENTRY_OBJECTS);
    menu_engine.push_back(ENTRY_PROTOTYPE);
    menu_engine.push_back(ENTRY_ATTRACT);
    menu_engine.push_back(ENTRY_BACK);

    menu_musictest.push_back(ENTRY_MUSIC1);
    menu_musictest.push_back(ENTRY_MUSIC2);
    menu_musictest.push_back(ENTRY_MUSIC3);
    menu_musictest.push_back(ENTRY_MUSIC4);
    menu_musictest.push_back(ENTRY_BACK);

    menu_about.push_back("CANNONBALL 0.3 © CHRIS WHITE 2014");
    menu_about.push_back("REASSEMBLER.BLOGSPOT.COM");
    menu_about.push_back(" ");
    menu_about.push_back("CANNONBALL IS FREE AND MAY NOT BE SOLD.");

    // Redefine menu text
    text_redefine.push_back("PRESS UP");
    text_redefine.push_back("PRESS DOWN");
    text_redefine.push_back("PRESS LEFT");
    text_redefine.push_back("PRESS RIGHT");
    text_redefine.push_back("PRESS ACCELERATE");
    text_redefine.push_back("PRESS BRAKE");
    text_redefine.push_back("PRESS GEAR");
    text_redefine.push_back("PRESS GEAR HIGH");
    text_redefine.push_back("PRESS START");
    text_redefine.push_back("PRESS COIN IN");
    text_redefine.push_back("PRESS MENU");
    text_redefine.push_back("PRESS VIEW CHANGE");
}

void Menu::init()
{   
    // If we got a new high score on previous time trial, then save it!
    if (outrun.ttrial.new_high_score)
    {
        outrun.ttrial.new_high_score = false;
        ttrial->update_best_time();
    }

    outrun.select_course(false, config.engine.prototype != 0);
    video.enabled = true;
    video.sprite_layer->set_x_clip(false); // Stop clipping in wide-screen mode.
    video.sprite_layer->reset();
    video.clear_text_ram();
    video.tile_layer->restore_tiles();
    ologo.enable(LOGO_Y);

    // Setup palette, road and colours for background
    oroad.stage_lookup_off = 9;
    oinitengine.init_road_seg_master();
    opalette.setup_sky_palette();
    opalette.setup_ground_color();
    opalette.setup_road_centre();
    opalette.setup_road_stripes();
    opalette.setup_road_side();
    opalette.setup_road_colour();
    otiles.setup_palette_hud();

    oroad.init();
    oroad.road_ctrl = ORoad::ROAD_R0;
    oroad.horizon_set = 1;
    oroad.horizon_base = HORIZON_DEST + 0x100;
    oinitengine.rd_split_state = OInitEngine::SPLIT_NONE;
    oinitengine.car_increment = 0;
    oinitengine.change_width = 0;

    outrun.game_state = GS_INIT;

    set_menu(&menu_main);
    refresh_menu();

    // Reset audio, so we can play tones
    osoundint.has_booted = true;
    osoundint.init();
//    cannonball::audio.clear_wav();

    frame = 0;
    message_counter = 0;

    if (config.cannonboard.enabled)
        display_message(cannonboard->started() ? "CANNONBOARD FOUND!" : "CANNONBOARD ERROR!");

    state = STATE_MENU;
}

void Menu::tick(Packet* packet)
{
    switch (state)
    {
        case STATE_MENU:
        case STATE_REDEFINE_KEYS:
        case STATE_REDEFINE_JOY:
            tick_ui();
            break;

        case STATE_DIAGNOSTICS:
            if (cabdiag->tick(packet))
            {
                init();
                set_menu(&menu_cannonboard);
                refresh_menu();
            }
            break;

        case STATE_TTRIAL:
            {
                int ttrial_state = ttrial->tick();

                if (ttrial_state == TTrial::INIT_GAME)
                {
                    cannonball::state = cannonball::STATE_INIT_GAME;
                    osoundint.queue_clear();
                }
                else if (ttrial_state == TTrial::BACK_TO_MENU)
                {
                    init();
                }
            }
            break;
    }
}

void Menu::tick_ui()
{
    // Skip odd frames at 60fps
    frame++;

    video.clear_text_ram();

    if (state == STATE_MENU)
    {
        tick_menu();
        draw_menu_options();
    }
    else if (state == STATE_REDEFINE_KEYS)
    {
        redefine_keyboard();
    }
    else if (state == STATE_REDEFINE_JOY)
    {
        redefine_joystick();
    }

    // Show messages
    if (message_counter > 0)
    {
        message_counter--;
        //ohud.blit_text_new(0, 1, msg.c_str(), ohud.GREY);
    }
     
    // Shift horizon
    if (oroad.horizon_base > HORIZON_DEST)
    {
        oroad.horizon_base -= 60 / config.fps;
        if (oroad.horizon_base < HORIZON_DEST)
            oroad.horizon_base = HORIZON_DEST;
    }
    // Advance road
    else
    {
        uint32_t scroll_speed = (config.fps == 60) ? config.menu.road_scroll_speed : config.menu.road_scroll_speed << 1;

        if (oinitengine.car_increment < scroll_speed << 16)
            oinitengine.car_increment += (1 << 14);
        if (oinitengine.car_increment > scroll_speed << 16)
            oinitengine.car_increment = scroll_speed << 16;
        uint32_t result = 0x12F * (oinitengine.car_increment >> 16);
        oroad.road_pos_change = result;
        oroad.road_pos += result;
        if (oroad.road_pos >> 16 > ROAD_END) // loop to beginning of track data
            oroad.road_pos = 0;
        oinitengine.update_road();
        oinitengine.set_granular_position();
        oroad.road_width_bak = oroad.road_width >> 16; 
        oroad.car_x_bak = -oroad.road_width_bak; 
        oinitengine.car_x_pos = oroad.car_x_bak;
    }

    // Do Animations at 30 fps
    if (config.fps != 60 || (frame & 1) == 0)
    {
        ologo.tick();
        osprites.sprite_copy();
        osprites.update_sprites();
    }

    // Draw FPS
    if (config.video.fps_count)
        ohud.draw_fps_counter(cannonball::fps_counter);

    oroad.tick();
}

void Menu::draw_menu_options()
{
    int8_t x = 0;

    // Find central column in screen. 
    int8_t y = 13 + ((ROWS - 13) >> 1) - ((menu_selected->size() * 2) >> 1);

    for (int i = 0; i < (int) menu_selected->size(); i++)
    {
        std::string s = menu_selected->at(i);

        // Centre the menu option
        x = 20 - (s.length() >> 1);
        ohud.blit_text_new(x, y, s.c_str(), ohud.GREEN);

        if (!is_text_menu)
        {
            // Draw minicar
            if (i == cursor)
                video.write_text32(ohud.translate(x - 3, y), roms.rom0.read32(TILES_MINICARS1));
            // Erase minicar from this position
            else
                video.write_text32(ohud.translate(x - 3, y), 0x20202020);
        }
        y += 2;
    }
}

// Draw a single line of text
void Menu::draw_text(std::string s)
{
    // Centre text
    int8_t x = 20 - (s.length() >> 1);

    // Find central column in screen. 
    int8_t y = 13 + ((ROWS - 13) >> 1) - 1;

    ohud.blit_text_new(x, y, s.c_str(), ohud.GREEN);
}

#define SELECTED(string) boost::starts_with(OPTION, string)

void Menu::tick_menu()
{
    
        // Tick Controls
    if (input.has_pressed(Input::DOWN) || oinputs.is_analog_r())
    {
        osoundint.queue_sound(sound::BEEP1);

        if (++cursor >= (int16_t) menu_selected->size())
            cursor = 0;
    }
    else if (input.has_pressed(Input::UP) || oinputs.is_analog_l())
    {
        osoundint.queue_sound(sound::BEEP1);

        if (--cursor < 0)
            cursor = menu_selected->size() - 1;
    }
    else if (input.has_pressed(Input::ACCEL) || input.has_pressed(Input::START) || oinputs.is_analog_select())
    {
        // Get option that was selected
        const char* OPTION = menu_selected->at(cursor).c_str();

        if (menu_selected == &menu_main)
        {
            switch (cursor)
            {
                case 0:
                    start_game(Outrun::MODE_ORIGINAL);
                    break;
            }
        }
        else if (menu_selected == &menu_gamemodes)
        {
 
        }
        else if (menu_selected == &menu_cont)
        {
 
        }
        else if (menu_selected == &menu_timetrial)
        {
 
        }
        else if (menu_selected == &menu_about)
        {
            set_menu(&menu_main);
        }
        else if (menu_selected == &menu_cannonboard)
        {
 
        }
        else if (menu_selected == &menu_video)
        {
 
        }
        else if (menu_selected == &menu_sound)
        {
 
        }
        else if (menu_selected == &menu_controls)
        {
 
        }
        else if (menu_selected == &menu_engine)
        {
 
        }
        else if (menu_selected == &menu_musictest)
        {
         
        }
        else
            set_menu(&menu_main);

        osoundint.queue_sound(sound::BEEP1);
        refresh_menu();
    }
    
}

// Set Current Menu
void Menu::set_menu(std::vector<std::string> *menu)
{
    menu_selected = menu;
    cursor = 0;

    is_text_menu = (menu == &menu_about);
}

// Refresh menu options with latest config data
void Menu::refresh_menu()
{
     
}

// Append Menu Text For A Particular Menu Entry
void Menu::set_menu_text(std::string s1, std::string s2)
{
    s1.append(s2);
    menu_selected->erase(menu_selected->begin() + cursor);
    menu_selected->insert(menu_selected->begin() + cursor, s1);
}

void Menu::redefine_keyboard()
{
    if (redef_state == 7 && config.controls.gear != config.controls.GEAR_SEPARATE) // Skip redefine of second gear press
        redef_state++;

    switch (redef_state)
    {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
            if (input.has_pressed(Input::MENU))
            {
                message_counter = 0;
                state = STATE_MENU;
            }
            else
            {
                draw_text(text_redefine.at(redef_state));
                if (input.key_press != -1)
                {
                    config.controls.keyconfig[redef_state] = input.key_press;
                    redef_state++;
                    input.key_press = -1;
                }
            }
            break;

        case 12:
            state = STATE_MENU;
            break;
    }
}

void Menu::redefine_joystick()
{
    if (redef_state == 3 && config.controls.gear != config.controls.GEAR_SEPARATE) // Skip redefine of second gear press
        redef_state++;

    switch (redef_state)
    {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            if (input.has_pressed(Input::MENU))
            {
                message_counter = 0;
                state = STATE_MENU;
            }
            else
            {
                draw_text(text_redefine.at(redef_state + 4));
                if (input.joy_button != -1)
                {
                    config.controls.padconfig[redef_state] = input.joy_button;
                    redef_state++;
                    input.joy_button = -1;
                }
            }
            break;

        case 8:
            state = STATE_MENU;
            break;
    }
}

// Display a contextual message in the top left of the screen
void Menu::display_message(std::string s)
{
  //  msg = s;
    message_counter = MESSAGE_TIME * config.fps;
}

bool Menu::check_jap_roms()
{
    if (config.engine.jap && !roms.load_japanese_roms())
    {
        display_message("JAPANESE ROMSET NOT FOUND");
        return false;
    }
    return true;
}

// Reinitalize Video, and stop audio to avoid crackles
void Menu::restart_video()
{
    #ifdef COMPILE_SOUND_CODE
    if (config.sound.enabled)
        cannonball::audio.stop_audio();
    #endif
    video.disable();
    video.init(&roms, &config.video);
    #ifdef COMPILE_SOUND_CODE
    osoundint.init();
    if (config.sound.enabled)
        cannonball::audio.start_audio();
    #endif
}

void Menu::start_game(int mode, int settings)
{
    // Enhanced Settings
    if (settings == 1)
    {
        if (!config.video.hires)
        {
            if (config.video.scale > 1)
                config.video.scale >>= 1;
        }

        if (!config.sound.fix_samples)
        {
            if (roms.load_pcm_rom(true))
                config.sound.fix_samples = 1;
        }

        config.set_fps(config.video.fps = 2);
        config.video.widescreen     = 1;
        config.video.hires          = 1;
        config.engine.level_objects = 1;
        config.engine.new_attract   = 1;
        config.engine.fix_bugs      = 1;
        config.sound.preview        = 1;

        restart_video();
    }
    // Original Settings
    else if (settings == 2)
    {
        if (config.video.hires)
        {
            config.video.scale <<= 1;
        }

        if (config.sound.fix_samples)
        {
            if (roms.load_pcm_rom(false))
                config.sound.fix_samples = 0;
        }

        config.set_fps(config.video.fps = 1);
        config.video.widescreen     = 0;
        config.video.hires          = 0;
        config.engine.level_objects = 0;
        config.engine.new_attract   = 0;
        config.engine.fix_bugs      = 0;
        config.sound.preview        = 0;

        restart_video();
    }
    // Otherwise, use whatever is already setup...
    else
    {
        config.engine.fix_bugs = config.engine.fix_bugs_backup;
    }

    if (check_jap_roms())
    {
        outrun.cannonball_mode = mode;
        cannonball::state = cannonball::STATE_INIT_GAME;
        osoundint.queue_clear();
    }
}

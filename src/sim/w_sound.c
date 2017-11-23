/* 
 * Portions Copyright (c) 2008 Deanna Phillips <deanna@sdf.lonestar.org>
 */

/* w_sound.c
 *
 * Micropolis, Unix Version.  This game was released for the Unix platform
 * in or about 1990 and has been modified for inclusion in the One Laptop
 * Per Child program.  Copyright (C) 1989 - 2007 Electronic Arts Inc.  If
 * you need assistance with this program, you may contact:
 *   http://wiki.laptop.org/go/Micropolis  or email  micropolis@laptop.org.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.  You should have received a
 * copy of the GNU General Public License along with this program.  If
 * not, see <http://www.gnu.org/licenses/>.
 * 
 *             ADDITIONAL TERMS per GNU GPL Section 7
 * 
 * No trademark or publicity rights are granted.  This license does NOT
 * give you any right, title or interest in the trademark SimCity or any
 * other Electronic Arts trademark.  You may not distribute any
 * modification of this program using the trademark SimCity or claim any
 * affliation or association with Electronic Arts Inc. or its employees.
 * 
 * Any propagation or conveyance of this program must include this
 * copyright notice and these terms.
 * 
 * If you convey this program (or any modifications of it) and assume
 * contractual liability for the program to recipients of it, you agree
 * to indemnify Electronic Arts for any liability that those contractual
 * assumptions impose on Electronic Arts.
 * 
 * You may not misrepresent the origins of this program; modified
 * versions of the program must be marked as such and not identified as
 * the original program.
 * 
 * This disclaimer supplements the one included in the General Public
 * License.  TO THE FULLEST EXTENT PERMISSIBLE UNDER APPLICABLE LAW, THIS
 * PROGRAM IS PROVIDED TO YOU "AS IS," WITH ALL FAULTS, WITHOUT WARRANTY
 * OF ANY KIND, AND YOUR USE IS AT YOUR SOLE RISK.  THE ENTIRE RISK OF
 * SATISFACTORY QUALITY AND PERFORMANCE RESIDES WITH YOU.  ELECTRONIC ARTS
 * DISCLAIMS ANY AND ALL EXPRESS, IMPLIED OR STATUTORY WARRANTIES,
 * INCLUDING IMPLIED WARRANTIES OF MERCHANTABILITY, SATISFACTORY QUALITY,
 * FITNESS FOR A PARTICULAR PURPOSE, NONINFRINGEMENT OF THIRD PARTY
 * RIGHTS, AND WARRANTIES (IF ANY) ARISING FROM A COURSE OF DEALING,
 * USAGE, OR TRADE PRACTICE.  ELECTRONIC ARTS DOES NOT WARRANT AGAINST
 * INTERFERENCE WITH YOUR ENJOYMENT OF THE PROGRAM; THAT THE PROGRAM WILL
 * MEET YOUR REQUIREMENTS; THAT OPERATION OF THE PROGRAM WILL BE
 * UNINTERRUPTED OR ERROR-FREE, OR THAT THE PROGRAM WILL BE COMPATIBLE
 * WITH THIRD PARTY SOFTWARE OR THAT ANY ERRORS IN THE PROGRAM WILL BE
 * CORRECTED.  NO ORAL OR WRITTEN ADVICE PROVIDED BY ELECTRONIC ARTS OR
 * ANY AUTHORIZED REPRESENTATIVE SHALL CREATE A WARRANTY.  SOME
 * JURISDICTIONS DO NOT ALLOW THE EXCLUSION OF OR LIMITATIONS ON IMPLIED
 * WARRANTIES OR THE LIMITATIONS ON THE APPLICABLE STATUTORY RIGHTS OF A
 * CONSUMER, SO SOME OR ALL OF THE ABOVE EXCLUSIONS AND LIMITATIONS MAY
 * NOT APPLY TO YOU.
 */
#ifdef WITH_SDL_MIXER
#include "SDL.h"
#include "SDL_mixer.h"
#endif

#include "sim.h"


#define SIM_NSOUNDS	47
#define SIM_NCHANNELS	32
#define DOZER_CHANNEL	0
#define DOZER_SOUND	"rumble.wav"

struct sound {
  char *id;
  char *file;
#ifdef WITH_SDL_MIXER
  Mix_Chunk *wave;
#else
  void *wave;
#endif
};

struct sound sounds[SIM_NSOUNDS] = {
  { "A",		"a.wav",		NULL },
  { "Aaah",		"aaah.wav",		NULL },
  { "Airport",		"airport.wav",		NULL },
  { "Beep",		"beep.wav",		NULL },
  { "Boing",		"boing.wav",		NULL },
  { "Bop",		"bop.wav",		NULL },
  { "Build",		"build.wav",		NULL },
  { "Bulldozer",	"bulldozer.wav",	NULL },
  { "Chalk",		"chalk.wav",		NULL },
  { "Coal",		"coal.wav",		NULL },
  { "Com",		"com.wav",		NULL },
  { "Computer",		"computer.wav",		NULL },
  { "Cuckoo",		"cuckoo.wav",		NULL },
  { "E",		"e.wav",		NULL },
  { "Eraser",		"eraser.wav",		NULL },
  { "Explosion-High",	"explosion-high.wav",	NULL },
  { "Explosion-Low",	"explosion-low.wav",	NULL },
  { "Fire",		"fire.wav",		NULL },
  { "HeavyTraffic",	"heavytraffic.wav",	NULL },
  { "HonkHonk-High",	"honkhonk-high.wav",	NULL },
  { "HonkHonk-Low",	"honkhonk-low.wav",	NULL },
  { "HonkHonk-Med",	"honkhonk-med.wav",	NULL },
  { "Ignition",		"ignition.wav",		NULL },
  { "Ind",		"ind.wav",		NULL },
  { "Monster",		"monster.wav",		NULL },
  { "Nuclear",		"nuclear.wav",		NULL },
  { "O",		"o.wav",		NULL },
  { "Oop",		"oop.wav",		NULL },
  { "Park",		"park.wav",		NULL },
  { "Player",		"player.wav",		NULL },
  { "Police",		"police.wav",		NULL },
  { "QuackQuack",	"quackquack.wav",	NULL },
  { "Query",		"query.wav",		NULL },
  { "Rail",		"rail.wav",		NULL },
  { "Res",		"res.wav",		NULL },
  { "Road",		"road.wav",		NULL },
  { "Rumble",		"rumble.wav",		NULL },
  { "Seaport",		"seaport.wav",		NULL },
  { "Siren",		"siren.wav",		NULL },
  { "Skid",		"skid.wav",		NULL },
  { "Sorry",		"sorry.wav",		NULL },
  { "Stadium",		"stadium.wav",		NULL },
  { "UhUh",		"uhuh.wav",		NULL },
  { "Whip",		"whip.wav",		NULL },
  { "Wire",		"wire.wav",		NULL },
  { "Woosh",		"woosh.wav",		NULL },
  { "Zone",		"zone.wav",		NULL }
};

static int SoundInitialized = 0;

#ifdef WITH_SDL_MIXER
/* Sound routines */


Mix_Chunk *rumble;


void
InitializeSound(void)
{
  int reserved_chans;
  char buf[256];

  if (SDL_Init(SDL_INIT_AUDIO) == -1) {
    fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
    return;
  }

  if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 1, 1024) == -1) {
    fprintf(stderr, "Mix_OpenAudio: %s\n", Mix_GetError());
    return;
  }

  reserved_chans = Mix_ReserveChannels(1);

  if (reserved_chans != 1) {
    fprintf(stderr, "Mix_ReserveChannels: %s\n", Mix_GetError());
    return;
  }

  if (Mix_AllocateChannels(SIM_NCHANNELS) == -1) {
    fprintf(stderr, "Mix_AllocateChannels: %s\n", Mix_GetError());
    return;
  }

  snprintf(buf, sizeof(buf), "%s/sounds/%s", ResourceDir, DOZER_SOUND);
  rumble = Mix_LoadWAV(buf);

  if (rumble == NULL) {
    printf("Mix_LoadWAV: %s\n", Mix_GetError());
    return;
  }

  SoundInitialized = 1;
}


void
ShutDownSound()
{
  int i;
  SoundInitialized = 0;

  for (i = 0; i < SIM_NSOUNDS; i++) {
    if (sounds[i].wave) {
      Mix_FreeChunk(sounds[i].wave);
      sounds[i].wave = NULL;
    }
  }
  if (rumble) {
    Mix_FreeChunk(rumble);
    rumble = NULL;
  }
  Mix_CloseAudio();
  SDL_Quit();
}


void
MakeSound(char *channel, char *id)
{
  char buf[256];
  int i;

  if (!UserSoundOn) return;
  if (!SoundInitialized) return;

  for (i = 0; i < SIM_NSOUNDS; i++) {
    if (!strcmp(sounds[i].id, id))
      break;
  }
  
  if (sounds[i].wave) {
    if (Mix_PlayChannel(-1, sounds[i].wave, 0) == -1)
      fprintf(stderr, "Mix_PlayChannel: %s\n", Mix_GetError());
    return;
  }

  snprintf(buf, sizeof(buf), "%s/sounds/%s", ResourceDir,
	   sounds[i].file);

  sounds[i].wave = Mix_LoadWAV(buf);

  if (sounds[i].wave == NULL) {
    fprintf(stderr, "Mix_LoadWAV: %s\n", Mix_GetError());
    return;
  }

  if (Mix_PlayChannel(-1, sounds[i].wave, 0) == -1)
    fprintf(stderr, "Mix_PlayChannel: %s\n", Mix_GetError());
}

void
StartBulldozer(void)
{
  if (!UserSoundOn) return;
  if (!SoundInitialized) return;

  if (Mix_PlayChannel(DOZER_CHANNEL, rumble, 4) == -1) {
    printf("Mix_PlayChannel: %s\n", Mix_GetError());
    return;
  }
}


void
StopBulldozer(void)
{
  if (!UserSoundOn) return;
  if (!SoundInitialized) return;

  Mix_HaltChannel(DOZER_CHANNEL);
}

#else /* WITH_SDL_MIXER */
void
InitializeSound()
{
  SoundInitialized = 1;
}

void
ShutDownSound()
{
  SoundInitialized = 0;
}

void
MakeSound(char *channel, char *id)
{
  char filename[256], player[256];
  static struct timeval last = {0, 0};
  struct timeval now;
  unsigned int diff;
  int i;
  pid_t pid;

  gettimeofday(&now, NULL);

  diff = ((now.tv_sec - last.tv_sec) * 1000000) +
    (now.tv_usec - last.tv_usec);
  
  if (diff < 100000)
    return;

  last = now;

  if (!UserSoundOn) return;
  if (!SoundInitialized) return;

  for (i = 0; i < SIM_NSOUNDS; i++) {
    if (!strcmp(sounds[i].id, id))
      break;
  }
 
  snprintf(filename, sizeof(filename), "%s/sounds/%s", ResourceDir,
	   sounds[i].file);

  snprintf(player, sizeof(player), "%s/sounds/player", ResourceDir);

  pid = fork();

  switch(pid) {
    case 0:
      execl(player, player, filename, NULL);
      exit(1);
      break;
    case -1:
      perror("fork failed");
      break;
    default:
      break;
  }
}

void
StartBulldozer(void)
{
  MakeSound(0, "Rumble");
}

void
StopBulldozer(void)
{
}
#endif


void
MakeSoundOn(SimView *view, char *channel, char *id)
{
  if (!UserSoundOn) return;
  if (!SoundInitialized) return;

  MakeSound(channel, id);
}


/* XXX comefrom: doKeyEvent */
void
SoundOff(void)
{
  ShutDownSound();
}


void
DoStartSound(char *channel, char *id)
{
  MakeSound(channel, id);
}

void
DoStopSound(char *id)
{
  StopBulldozer();
}

int
SoundCmd(CLIENT_ARGS)
{
  if (!strcmp(argv[2], "Rumble"))
    StartBulldozer();
  else
    MakeSound(NULL, argv[2]);
  return 0;
}

int
DozerCmd(CLIENT_ARGS)
{
  StopBulldozer();
  return 0;
}

void
sound_command_init(void)
{
  Tcl_CreateCommand(tk_mainInterp, "playsound", SoundCmd,
		    (ClientData)NULL, (void (*)()) NULL);
  Tcl_CreateCommand(tk_mainInterp, "stopdozer", DozerCmd,
		    (ClientData)NULL, (void (*)()) NULL);
}

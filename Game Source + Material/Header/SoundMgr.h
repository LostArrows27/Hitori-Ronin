#ifndef SOUNDMGR_H
#define SOUNDMGR_H

#include <map>
#include <string>
#include <iostream>
#include <SDL_mixer.h>

#define FREQ 44100
#define CHUNK_SIZE 2048 // 2Mb i think so

using EffectMap = std::map<std::string, Mix_Chunk*>; // for playing effect
using MusikMap = std::map<std::string, Mix_Music*>;  // for playing musicc

class SoundMgr {

    public:
        void Clean();

        void PlayMusik(std::string id);
        void LoadMusik(std::string id, std::string source);

        void PlayEffect(std::string id);
        void LoadEffect(std::string id, std::string source);

        inline static SoundMgr* Instance(){return s_Instance = (s_Instance != nullptr)? s_Instance : new SoundMgr();}

    private:
        SoundMgr();
        MusikMap m_MusicMap;
        EffectMap m_EffectMap;
        static SoundMgr* s_Instance;
};

#endif // SOUNDMGR_H

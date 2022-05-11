#ifndef SEQANIMATION_H
#define SEQANIMATION_H

#include <map>
#include <string>
#include <vector>
#include "SDL.h"
#include "TextureMgr.h"
#include "Transform.h"

struct Sequence {
    int Speed;
    int FrameCount;
    int Width, Height;
    std::vector<std::string> TextureIDs;
};

class SeqAnimation {

    public:
        SeqAnimation();
        ~SeqAnimation();

        void Update(Transform* tf);
        void Draw(Transform* tf);
        void Parse(std::string source);
        void SetCurrSeq(std::string seqID);

    private:
        int m_CurrFrame;
        Sequence* m_CurrSeq;
        std::map<std::string, Sequence*> m_SeqMap;
};

#endif // SEQANIMATION_H

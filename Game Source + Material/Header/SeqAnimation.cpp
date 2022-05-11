#include "SeqAnimation.h"
#include "tinyxml.h"
#include "iostream"

SeqAnimation::SeqAnimation(){}

SeqAnimation::~SeqAnimation(){
    m_CurrSeq->TextureIDs.clear();
    m_CurrSeq->TextureIDs.shrink_to_fit();
    m_SeqMap.clear();
}

void SeqAnimation::Draw(Transform* tf){
    TextureMgr::Instance()->Draw(tf);
}

void SeqAnimation::Update(Transform* tf){

    if(m_CurrSeq->FrameCount > 1)
        m_CurrFrame = (SDL_GetTicks()/m_CurrSeq->Speed) % m_CurrSeq->FrameCount;
    else
        m_CurrFrame = 0;

    tf->TextureID = m_CurrSeq->TextureIDs[m_CurrFrame];
    tf->Width =  m_CurrSeq->Width;
    tf->Height =  m_CurrSeq->Height;
}

void SeqAnimation::SetCurrSeq(std::string seqID){
    if(m_SeqMap.count(seqID) > 0)
        m_CurrSeq = m_SeqMap[seqID];
    else
        std::cout << "Sequence wrong:" << seqID << std::endl;
}

void SeqAnimation::Parse(std::string source){

    TiXmlDocument xml;
    xml.LoadFile(source);
    if(xml.Error())
        std::cout << "Failed to parse: " << source << xml.ErrorDesc() << std::endl;

    TiXmlElement* root = xml.RootElement();
    for(TiXmlElement* e=root->FirstChildElement(); e!= nullptr; e=e->NextSiblingElement()){
        if(e->Value() == std::string("sequence")){
            Sequence* seq = new Sequence();
            std::string seqID = e->Attribute("id");
            e->Attribute("speed", &seq->Speed);
            e->Attribute("width", &seq->Width);
            e->Attribute("height", &seq->Height);
            e->Attribute("frameCount", &seq->FrameCount);

            for(TiXmlElement* frame=e->FirstChildElement(); frame!= nullptr; frame=frame->NextSiblingElement())
                seq->TextureIDs.push_back(frame->Attribute("texture"));

            m_SeqMap[seqID] = seq;
        }
    }

    std::cout << source << " animation parsed!" << std::endl;
}



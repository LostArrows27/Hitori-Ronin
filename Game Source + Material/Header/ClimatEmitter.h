#ifndef WEATHEREMITTER_H
#define WEATHEREMITTER_H

#include "Particle.h"
#include "Transform.h"

#define DUST_PARTICLE_COUNT 50
#define RAIN_PARTICLE_COUNT 800
#define SNOW_PARTICLE_COUNT 400
#define THUNDER_PARTICLE_COUNT 1

// based on this, will have a certain "particle" on your screen

// render Thunder, dust, rain ,snow

enum Climat {DUST=0, RAIN, SNOW, LIGTHNING};

class ClimatEmitter {

    public:
        ClimatEmitter(Climat clmt = DUST){
            InitParticles(clmt);
        }

        ~ClimatEmitter(){
            for(auto particle : m_Particles)
                delete particle;
            m_Particles.clear();
        }

        void InitParticles(Climat clmt=DUST){

            m_CurrClimat = clmt;
            m_Particles.clear();
            m_PartTextrID.clear();

            switch(m_CurrClimat){

                case RAIN:
                    m_PartTextrID = {"rain1", "rain2", "rain3"};
                    m_ParticleCount = RAIN_PARTICLE_COUNT; break;

                case SNOW:
                    m_PartTextrID = {"snow1", "snow2", "snow3"};
                    m_ParticleCount = SNOW_PARTICLE_COUNT; break;

                case LIGTHNING:
                    m_PartTextrID = {"ligth1", "ligth2", "ligth3"};
                    m_ParticleCount = THUNDER_PARTICLE_COUNT; break;

                default:
                    m_PartTextrID = {"dust1", "dust2", "dust3"};
                    m_ParticleCount = DUST_PARTICLE_COUNT; break;
            }

            for(int i=0; i < m_ParticleCount; i++)
                m_Particles.push_back(NewParticle());
        }

        void UpdateParticles(float dt){
            for(int i=0; i < m_Particles.size(); i++){

                if(m_Particles[i]->IsDead()){
                    delete m_Particles[i];
                    m_Particles[i] = NewParticle();
                }
                else{
                    m_Particles[i]->Move(dt);
                }
                // if particle dead hay lifetime = 0,
                // then we create new particle and delete old 1
                // else, we keep the particle moving still as before
            }
        }

        void RenderParticles(){
            for(auto particle : m_Particles)
                particle->Show();
        }

    private:
        Particle* NewParticle(){
            int index = Helpers::RandI(0, m_PartTextrID.size());
            switch(m_CurrClimat){
                case RAIN: return RainParticle(m_PartTextrID[index]); break;
                case SNOW: return SnowParticle(m_PartTextrID[index]); break;
                case LIGTHNING: return ThunderParticle(m_PartTextrID[index]); break;
                default: return DustParticle(m_PartTextrID[index]);
            }
        }

        Particle* RainParticle(std::string textrID){
            SDL_Rect vp = Engine::Instance()->GetViewPort();
            float x = Helpers::RandI(0, vp.w);
            Uint32 lifetime = Helpers::RandI(800, 2000);
            Vector2D vel(Helpers::RandI(-1, 1), Helpers::RandI(10, 15));
            return (new Particle(Transform(x, 0, 0, 0, textrID), vel, lifetime));
        }

        Particle* SnowParticle(std::string textrID){
            SDL_Rect vp = Engine::Instance()->GetViewPort();
            float x = Helpers::RandI(0, vp.w);
            Uint32 lifetime = Helpers::RandI(5000, 8000);
            Vector2D vel(Helpers::RandI(-2, 2), Helpers::RandI(1, 4));
            return (new Particle(Transform(x, 0, 0, 0, textrID), vel, lifetime));
            // cause of this so we have a 2 line of snow on the beginnning
        }

        Particle* DustParticle(std::string textrID){
            SDL_Rect vp = Engine::Instance()->GetViewPort();
            float y = Helpers::RandI(0, vp.h);
            Uint32 lifetime = Helpers::RandI(4000, 9000);
            Vector2D vel(Helpers::RandI(-10, -1), Helpers::RandI(-1, 1));
            return (new Particle(Transform(vp.w, y, 0, 0, textrID), vel, lifetime));
        }

        Particle* ThunderParticle(std::string textrID){
            SDL_Rect vp = Engine::Instance()->GetViewPort();
            float x = Helpers::RandI(0, vp.w);
            float y = Helpers::RandI(0, 100);
            Uint32 lifetime = Helpers::RandI(600, 1200);
            return (new Particle(Transform(x, y, 0, 0, textrID), Vector2D(0,0), lifetime));
        }

    private:
        Climat m_CurrClimat;
        Uint32 m_ParticleCount; // count your certaini particle on screen
        std::vector<Particle*> m_Particles; // vector contain all the particle
        std::vector<std::string> m_PartTextrID;
};

#endif // WEATHEREMITTER_H

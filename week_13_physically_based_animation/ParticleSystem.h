#pragma once
#include "DataStructure/Vector3D.h"

typedef Vector3D<float> TV;

class Particle
{
public:
	Vector3D<float> pos, vel;
	float mass = 1.0;
};

class Sphere
{
public:
	TV center;
	float radius;

	float getSignedDistance(const TV& pos)
	{
		return (pos - center).getMagnitude() - radius;
	}

	TV getNormal(const TV& pos)
	{
		return (pos - center).getNormalized();
	}
};

class ParticleSystem
{
public:
	std::vector<Particle> particles;
	Sphere obj;

	void initParticleSystem()
	{
		const int num_particles = 2000;
		particles.resize(num_particles);

		float pi = 3.14;

		for (int p = 0; p < particles.size(); ++p)
		{
			TV& pos(particles[p].pos);
			TV& vel(particles[p].vel);
			float& m = particles[p].mass;

			float theta = 2 * pi * ((float)rand() / (float)RAND_MAX);
			float x = 0.2 * cos(theta);
			float z = 0.2 * sin(theta);

			vel = TV(x, 1.5f, z);
		}
	}

	void advanceOneTimeStep(const float& dt)
	{

		const TV g = TV(0.0, -4.8, 0.0);
		int randome = rand() % particles.size();

		for (int p = 0; p < particles.size(); ++p)
		{
			if (particles[randome].pos.x_ && 0 || particles[randome].pos.y_ == 0 && particles[randome].pos.z_ == 0)
			{
				particles[randome].vel += g * dt;
				particles[randome].pos += particles[randome].vel * dt;
			}
		}

		for (int p = 0; p < particles.size(); ++p)
		{
			if (particles[p].pos.x_ != 0 && particles[p].pos.y_ != 0 && particles[p].pos.z_ != 0)
			{
				particles[p].vel += g * dt;
				particles[p].pos += particles[p].vel * dt;
			}
		}

		// ground collision
		for (int p = 0; p < particles.size(); ++p)
		{
			if (particles[p].pos.y_ < 0.0f)
			{
				particles[p].vel.y_ = 0.0;

			}
		}
	}
};
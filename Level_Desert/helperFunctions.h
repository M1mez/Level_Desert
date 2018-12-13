#pragma once
#include <string>
#include <iostream>

extern float playerBounds;
extern float planeRadius;

bool endsWith(std::string const &fullString, std::string const &ending);
std::pair<float, float> getPos2InBounds();
float randomFloatBetween(float lo, float hi);
float calculatePosOneAxis(float changeAxis, float stayAxis, float bounds = playerBounds);
float getDistance(glm::vec2 first, glm::vec2 sec);
void addVertexWithNormals(float x, float z, float y, float vertices[], int &count, bool normals = true);
bool chance(float percent);

inline bool chance(float percent) { return randomFloatBetween(0.0f, 100.0f) < percent; }
// does the given string end with another given string?
inline bool endsWith(std::string const &fullString, std::string const &ending) {
	return fullString.length() >= ending.length()
		&& 0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending);
}
// get x locations with no object closer to another one than minDist
inline int getValidVec2InBounds(std::vector <glm::vec2> &locationList, glm::vec2 *newVec, float minDist)
{
	bool xPrio = chance(50.0f);
	bool alreadyExists;
	int tries = 0, maxTries = 50;

	do
	{
		if (xPrio) {
			newVec->x = randomFloatBetween(-planeRadius, planeRadius);
			newVec->y = calculatePosOneAxis(randomFloatBetween(-planeRadius, planeRadius), newVec->x, planeRadius);
		}
		else
		{
			newVec->y = randomFloatBetween(-planeRadius, planeRadius);
			newVec->x = calculatePosOneAxis(randomFloatBetween(-planeRadius, planeRadius), newVec->y, planeRadius);
		}

		alreadyExists = false;
		for (auto loc : locationList)
		{
			if (getDistance(loc, *newVec) < minDist)
			{
				alreadyExists = true;
				break;
			}
		}
		if(tries++ >= maxTries)
		{
			std::cout << "WARNING::HELPER::GETVALIDVEC2INBOUNDS_MAXTRIES_REACHED" << std::endl;
			return -1;
		}
	} while (alreadyExists);
	return 0;
}
inline float randomFloatBetween(float lo, float hi)
{
	const float random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	const float diff = hi - lo;
	float r = random * diff;
	return lo + r;
}
inline int randomIntBetween(int lo, int hi){ return rand() % hi + lo; }
// get distance between 2 points
inline float getDistance(glm::vec2 first, glm::vec2 sec){ return glm::distance(first, sec);}
// returns valid axis-position after providing a suggested value
inline float calculatePosOneAxis(float changeAxis, float stayAxis, float bounds)
{
	short negativeIndicator = changeAxis / abs(changeAxis);
	double dblChangeAxis = changeAxis;
	double dblstayAxis = stayAxis;
	double dblbounds = bounds;

	double posFloat = sqrt((dblChangeAxis * dblChangeAxis) + (dblstayAxis * dblstayAxis));
	if (posFloat <= dblbounds) return changeAxis;


	return 0.0f; //(sqrt((dblbounds * dblbounds) - (dblstayAxis * dblstayAxis)));
}
// incase we need normals for our vertices, just like for the glass walls
inline void addVertexWithNormals(float x, float z, float y, float vertices[], int &count, bool normals)
{
	vertices[count++] = x;
	vertices[count++] = y;
	vertices[count++] = z;
	if (normals) vertices[count++] = -x;
	if (normals) vertices[count++] = 0.0f;
	if (normals) vertices[count++] = -z;
}
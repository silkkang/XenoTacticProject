#pragma once

enum class AnimationLoopTypes
{
	Single,
	Loop,
	//PingPong,
};

struct AnimationFrame
{
	std::string texId;
	sf::IntRect texCoord;

	AnimationFrame() {}
	AnimationFrame(const std::string& texId, const sf::IntRect& texCoord) : texId(texId), texCoord(texCoord) {}
};

struct AnimationClip
{
	std::string id;
	AnimationLoopTypes loopType = AnimationLoopTypes::Loop;
	int fps = 30;

	std::vector<AnimationFrame> frames;

	bool loadFromFile(const std::string& filePath);

	void setId(const std::string& newId) { id = newId; }
	void setFps(int newFps) { fps = newFps; }
	void setLoopType(AnimationLoopTypes lt) { loopType = lt; }
	void addFrame(const std::string& texId,
		const sf::IntRect& rect)
	{
		frames.emplace_back(texId, rect);
	}
};


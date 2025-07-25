#pragma once
class SceneMgr : public Singleton<SceneMgr>
{
	friend class Singleton<SceneMgr>;

protected:
	SceneMgr() = default;
	~SceneMgr() = default;

	std::vector<Scene*> scenes;

	SceneIds startScene = SceneIds::Round1;
	SceneIds currentScene = SceneIds::None;
	SceneIds nextScene = SceneIds::None;

	sf::RenderWindow* m_window = nullptr;
public:
	void Init(sf::RenderWindow& window);
	void Release();

	Scene* GetCurrentScene() { return scenes[(int)currentScene]; }
	SceneIds GetCurrentSceneId() const { return currentScene; }
	void ChangeScene(SceneIds id);

	void Update(float dt);
	void Draw(sf::RenderWindow& window);
};

#define SCENE_MGR (SceneMgr::Instance())


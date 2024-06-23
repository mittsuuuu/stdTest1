#pragma once
class Scene;
class SceneManager
{
	public:
		SceneManager();
		SceneManager(const SceneManager&) = delete;
		SceneManager &operator=(const SceneManager&) = delete;
		~SceneManager();
	private:
		Scene* mScene;

	public:
		void update();
		void draw() const;
};
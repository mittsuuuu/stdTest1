#pragma once

class Scene
{
	protected:
		Scene() {}

	public:
		//コピー禁止
		Scene(const Scene&) = delete;
		Scene& operator=(const Scene&) = delete;

		//仮想関数化したデストラクタ
		virtual ~Scene() = default;

		virtual Scene* update() = 0;
		virtual void draw() const = 0;
};
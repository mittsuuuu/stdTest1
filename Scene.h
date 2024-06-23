#pragma once

class Scene
{
	protected:
		Scene() {}

	public:
		//�R�s�[�֎~
		Scene(const Scene&) = delete;
		Scene& operator=(const Scene&) = delete;

		//���z�֐��������f�X�g���N�^
		virtual ~Scene() = default;

		virtual Scene* update() = 0;
		virtual void draw() const = 0;
};
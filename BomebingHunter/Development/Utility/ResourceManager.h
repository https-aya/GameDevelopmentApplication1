#pragma once

#include <map>
#include <string>
#include <vector>

struct MaterialParam
{
	std::string file_path;
	int all_num;
	int num_x;
	int num_y;
	int size_x;
	int size_y;
};

class ResourceManager
{
private:
	//���N���X�̃|�C���^�i�A�h���X�̐�ɃC���X�^���X�𐶐�����j
	static ResourceManager* instance;

	//�摜�i�[�R���e�i
	std::map<std::string, std::vector<int>> images_container;

	//�����i�[�R���e�i
	std::map<std::string, std::vector<int>> sounds_container;

private:
	/*�R���X�g���N�^�� private�ɂ��邱�Ƃ�
	���N���X�̃����o�֐��ł����C���X�^���X�𐶐��ł��Ȃ��悤�ɂ���*/
	ResourceManager() = default;

	/*�R�s�[�K�[�h
	 �N���X�O�ŃC���X�^���X�𐶐����ēn�����Ƃ��ł��Ȃ��悤�ɂ���*/
	ResourceManager(ResourceManager& v) = delete;
	ResourceManager& operator=(const ResourceManager& v) = delete;
	//�`�R�s�[�K�[�h


public:
	//�f�X�g���N�^
	~ResourceManager() = default;

public:
	//�C���X�^���X�擾���鏈��
	static ResourceManager* GetInstance();
	//�C���X�^���X�폜���鏈��
	static void DeleteInstance();

public:

	/*
	*�摜�擾����
	* @param file_name �t�@�C���p�X
	* @param all_num	�摜�̑���
	* @param num_x		���̑���
	* @param num_y		�c�̑���
	* @param size_x		���̃T�C�Y�ipx�j
	* @param size_y		�c�̃T�C�Y (px)
	* @return	�ǂݍ��񂾉摜�n���h����std::vector�z��
	*/
	const std::vector<int>& GetImages(std::string file_name, int all_num = 1,
		int num_x = 1, int num_y = 1, int size_x = 0, int size_y = 0);
	const std::vector<int>& GetImages(const char* file_name, int all_num = 1,
		int num_x = 1, int num_y = 1, int size_x = 0, int size_y = 0);
	const std::vector<int>& GetImages(MaterialParam element);

	/*
	* �����擾����
	* @param file_name �t�@�C���p�X
	* @return �ǂݍ��񂾉����n���h����std::vector�z��
	*/
	const std::vector<int>& GetSounds(std::string file_name);

	/**
	* ���ׂẲ摜�Ɖ������폜����
	* @param material_handle �폜�������摜�n���h����std::vector�z��
	* @param sounds_handle �폜�����������n���h����std::vector�z��
	*/
	void UnloadResourcesAll();

private:
	/**
	* �摜�n���h����ǂݍ��݃��\�[�X���쐬����
	* @param file_name �t�@�C���p�X
	*/
	void CreateImagesResource(std::string file_name);
	/*
	*�摜�n���h����ǂݍ��݃��\�[�X���쐬����
	* @param file_name �t�@�C���p�X
	* @param all_num	�摜�̑���
	* @param num_x		���̑���
	* @param num_y		�c�̑���
	* @param size_x		���̃T�C�Y�ipx�j
	* @param size_y		�c�̃T�C�Y (px)
	*/
	void CreateImagesResource(std::string file_name, int all_num, int num_x,
		int num_y, int size_x, int size_y);

	/*
	* �����n���h����ǂݍ��݃��\�[�X���쐬����
	* @param file_name �t�@�C���p�X
	*/
	void CreateSoundsResource(std::string file_name);
};


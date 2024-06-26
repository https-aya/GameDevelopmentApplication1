#include "ResourceManager.h"
#include "DxLib.h"

//静的メンバ変数定義
ResourceManager* ResourceManager::instance = nullptr;		//クラスのインスタンスのポインタ

///<summary>
///リソース管理クラスのインスタンス取得する処理
///</summary>
/// <returns>クラスのポインタ</returns>
ResourceManager* ResourceManager::GetInstance()
{
	//インスタンスが無ければ、生成する
	if (instance == nullptr)
	{
		instance = new ResourceManager();
	}

	//自分自身のポインタを返却する
	return instance;
}

///<summary>
///リソース管理クラスのインスタンス削除処理
///</summary>
void ResourceManager::DeleteInstance()
{
	//インスタンスが存在していれば、削除する
	if (instance != nullptr)
	{
		instance->UnloadResourcesAll();
		delete instance;
		instance = nullptr;
	}
}

/*
	*画像取得処理
	* @param file_name ファイルパス
	* @param all_num	画像の総数
	* @param num_x		横の総数
	* @param num_y		縦の総数
	* @param size_x		横のサイズ（px）
	* @param size_y		縦のサイズ (px)
	* @return	読み込んだ画像ハンドルのstd::vector配列
*/
const std::vector<int>& ResourceManager::GetImages(std::string file_name, int
	all_num, int num_x, int num_y, int size_x, int size_y)
{
	//コンテナ内に指定ファイルが無ければ、生成する
	if (images_container.count(file_name) == NULL)
	{
		if (all_num == 1)
		{
			CreateImagesResource(file_name);
		}
		else
		{
			CreateImagesResource(file_name, all_num, num_x, num_y, size_x, size_y);
		}

	}

	return images_container[file_name];
}
const std::vector<int>& ResourceManager::GetImages(const char* file_name, int
	all_num, int num_x, int num_y, int size_x, int size_y)
{
	return GetImages(std::string(file_name), all_num, num_x, num_y, size_x, size_y);
}
const std::vector<int>& ResourceManager::GetImages(MaterialParam element)
{
	return GetImages(element.file_path, element.all_num, element.num_x,
		element.num_y, element.size_x, element.size_y);
}

/*
	* 音源取得処理
	* @param file_name ファイルパス
	* @return 読み込んだ音源ハンドルのstd::vector配列
	*/
const std::vector<int>& ResourceManager::GetSounds(std::string file_name)
{
	if (sounds_container.count(file_name) == NULL)
	{
		CreateSoundsResource(file_name);
	}

	return sounds_container[file_name];
}

/**
	* すべての画像と音源を削除する
	* @param material_handle 削除したい画像ハンドルのstd::vector配列
	* @param sounds_handle 削除したい音源ハンドルのstd::vector配列
	*/
void ResourceManager::UnloadResourcesAll()
{
	//コンテナ内に画像が有れば、削除する
	if (images_container.size() != NULL)
	{
		//すべての画像を削除
		for (std::pair<std::string, std::vector<int>>value : images_container)
		{
			DeleteSharingGraph(value.second[0]);
			value.second.clear();
		}

		//コンテナを開放
		images_container.clear();
	}
	//コンテナ内に音源があれば、削除する
	if (sounds_container.size() != NULL)
	{
		//すべての音源を削除
		for (std::pair<std::string, std::vector<int>>value : sounds_container)
		{
			DeleteSoundMem(value.second[0]);
			value.second.clear();
		}

		//コンテナの開放
		sounds_container.clear();
	}

	return;
}

/**
	* 画像ハンドルを読み込みリソースを作成する
	* @param file_name ファイルパス
	*/
void ResourceManager::CreateImagesResource(std::string file_name)
{
	//指定されたファイルを読み込む
	int handle = LoadGraph(file_name.c_str());

	//エラーチェック
	if (handle == -1)
	{
		throw(file_name + "がありません\n");
	}

	//コンテナに読み込んだ画像を追加する
	images_container[file_name].push_back(handle);
}

/*
	*画像ハンドルを読み込みリソースを作成する
	* @param file_name ファイルパス
	* @param all_num	画像の総数
	* @param num_x		横の総数
	* @param num_y		縦の総数
	* @param size_x		横のサイズ（px）
	* @param size_y		縦のサイズ (px)
	*/
void ResourceManager::CreateImagesResource(std::string file_name, int all_num,
	int num_x, int num_y, int size_x, int size_y)
{
	//指定されたファイルを読み込む
	int* handle = new int[all_num];
	int err = LoadDivGraph(file_name.c_str(), all_num, num_x, num_y, size_x,
		size_y, handle);

	//エラーチェック
	if (err == -1)
	{
		throw(file_name + "がありません\n");
	}

	//コンテナに読み込んだ画像を追加する
	for (int i = 0; i < all_num; i++)
	{
		images_container[file_name].push_back(handle[i]);
	}

	//動的メモリの開放
	delete[] handle;
}

/*
* 音源ハンドルを読み込みリソースを作成する
* @param file_name ファイルパス
*/
void ResourceManager::CreateSoundsResource(std::string file_name)
{
	//指定されたファイルを読み込む
	int handle = LoadSoundMem(file_name.c_str());

	//エラーチェック
	if (handle == -1)
	{
		throw(file_name + "がありません\n");
	}

	//コンテナに読み込んだ音源を追加する
	sounds_container[file_name].push_back(handle);
}
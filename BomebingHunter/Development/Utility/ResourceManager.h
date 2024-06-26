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
	//自クラスのポインタ（アドレスの先にインスタンスを生成する）
	static ResourceManager* instance;

	//画像格納コンテナ
	std::map<std::string, std::vector<int>> images_container;

	//音源格納コンテナ
	std::map<std::string, std::vector<int>> sounds_container;

private:
	/*コンストラクタを privateにすることで
	自クラスのメンバ関数でしかインスタンスを生成できないようにする*/
	ResourceManager() = default;

	/*コピーガード
	 クラス外でインスタンスを生成して渡すことができないようにする*/
	ResourceManager(ResourceManager& v) = delete;
	ResourceManager& operator=(const ResourceManager& v) = delete;
	//～コピーガード


public:
	//デストラクタ
	~ResourceManager() = default;

public:
	//インスタンス取得する処理
	static ResourceManager* GetInstance();
	//インスタンス削除する処理
	static void DeleteInstance();

public:

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
	const std::vector<int>& GetImages(std::string file_name, int all_num = 1,
		int num_x = 1, int num_y = 1, int size_x = 0, int size_y = 0);
	const std::vector<int>& GetImages(const char* file_name, int all_num = 1,
		int num_x = 1, int num_y = 1, int size_x = 0, int size_y = 0);
	const std::vector<int>& GetImages(MaterialParam element);

	/*
	* 音源取得処理
	* @param file_name ファイルパス
	* @return 読み込んだ音源ハンドルのstd::vector配列
	*/
	const std::vector<int>& GetSounds(std::string file_name);

	/**
	* すべての画像と音源を削除する
	* @param material_handle 削除したい画像ハンドルのstd::vector配列
	* @param sounds_handle 削除したい音源ハンドルのstd::vector配列
	*/
	void UnloadResourcesAll();

private:
	/**
	* 画像ハンドルを読み込みリソースを作成する
	* @param file_name ファイルパス
	*/
	void CreateImagesResource(std::string file_name);
	/*
	*画像ハンドルを読み込みリソースを作成する
	* @param file_name ファイルパス
	* @param all_num	画像の総数
	* @param num_x		横の総数
	* @param num_y		縦の総数
	* @param size_x		横のサイズ（px）
	* @param size_y		縦のサイズ (px)
	*/
	void CreateImagesResource(std::string file_name, int all_num, int num_x,
		int num_y, int size_x, int size_y);

	/*
	* 音源ハンドルを読み込みリソースを作成する
	* @param file_name ファイルパス
	*/
	void CreateSoundsResource(std::string file_name);
};


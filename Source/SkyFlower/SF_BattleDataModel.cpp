#include "SF_BattleDataModel.h"

USF_BattleDataModel::USF_BattleDataModel()
	//: BattleDataMap()
{
}

// ToDo
/// @brief 各ステージ分だけ処理を行う
/// @brief ステージ数やウェーブ数、敵の数などを更新したら
/// @brief この関数を呼び出し、情報を更新させる
//void USF_BattleDataModel::LoadData()
//{
//	const int StageNum = BattleDataMap.Num();
//
//	TMap<uint8, FSF_BattleStageInfo> NewBattleDataMap;
//	// ステージの数だけ繰り返し
//	for (int i = 0; i < StageNum; i++)
//	{
//		// 更新用
//		FSF_BattleStageInfo NewBattleStageInfo;
//
//		// 指定したステージ情報を検索
//		// 情報が無ければログを出し、処理を中断
//		FSF_BattleStageInfo* const BattleStageInfo = BattleDataMap.Find(i);
//		if (!BattleStageInfo)
//		{
//			// ログを出す
//			return;
//		}
//
//		// ウェーブの数だけ繰り返し
//		for (FSF_WaveInfo& Wave_itr : BattleStageInfo->WaveInfoList)
//		{
//
//			// 敵の数だけ繰り返し
//			for (FSF_GeneratEnemyInfo& Enemy_itr : Wave_itr.GenerateEnemyList)
//			{
//
//			}
//		}
//	}
//}
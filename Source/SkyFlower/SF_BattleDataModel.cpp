#include "SF_BattleDataModel.h"

USF_BattleDataModel::USF_BattleDataModel()
	//: BattleDataMap()
{
}

// ToDo
/// @brief �e�X�e�[�W�������������s��
/// @brief �X�e�[�W����E�F�[�u���A�G�̐��Ȃǂ��X�V������
/// @brief ���̊֐����Ăяo���A�����X�V������
//void USF_BattleDataModel::LoadData()
//{
//	const int StageNum = BattleDataMap.Num();
//
//	TMap<uint8, FSF_BattleStageInfo> NewBattleDataMap;
//	// �X�e�[�W�̐������J��Ԃ�
//	for (int i = 0; i < StageNum; i++)
//	{
//		// �X�V�p
//		FSF_BattleStageInfo NewBattleStageInfo;
//
//		// �w�肵���X�e�[�W��������
//		// ��񂪖�����΃��O���o���A�����𒆒f
//		FSF_BattleStageInfo* const BattleStageInfo = BattleDataMap.Find(i);
//		if (!BattleStageInfo)
//		{
//			// ���O���o��
//			return;
//		}
//
//		// �E�F�[�u�̐������J��Ԃ�
//		for (FSF_WaveInfo& Wave_itr : BattleStageInfo->WaveInfoList)
//		{
//
//			// �G�̐������J��Ԃ�
//			for (FSF_GeneratEnemyInfo& Enemy_itr : Wave_itr.GenerateEnemyList)
//			{
//
//			}
//		}
//	}
//}
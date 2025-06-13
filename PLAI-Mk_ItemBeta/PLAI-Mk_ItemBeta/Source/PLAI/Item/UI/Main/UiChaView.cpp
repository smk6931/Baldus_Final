// Fill out your copyright notice in the Description page of Project Settings.


#include "UiChaView.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "PLAI/Item/Login/UserStruct.h"

void UUiChaView::SetUiChaView(FUserFullInfo UserFullInfo)
{
	NameCha->SetText(FText::FromString(UserFullInfo.character_info.character_name));
	JobCha->SetText(FText::FromString(UserFullInfo.character_info.job));
	LevCha->SetText(FText::AsNumber(UserFullInfo.character_info.level));
	
	ExpPercent->SetText(FText::FromString(FString::Printf(
		TEXT("%.3f"),static_cast<float>(UserFullInfo.character_info.current_exp)/static_cast<float>(UserFullInfo.character_info.max_exp))));
	ExpCha->SetText(FText::AsNumber(UserFullInfo.character_info.current_exp));
	MaxExpCha->SetText(FText::AsNumber(UserFullInfo.character_info.max_exp));
	ExpBar->SetPercent(static_cast<float>(UserFullInfo.character_info.current_exp) /  static_cast<float>(UserFullInfo.character_info.max_exp));

	CurrentHp->SetText(FText::AsNumber(UserFullInfo.character_info.CurrentHp));
	MaxHp->SetText(FText::AsNumber(UserFullInfo.character_info.MaxHp));
	HpBar->SetPercent(static_cast<float>(UserFullInfo.character_info.current_exp) /  static_cast<float>(UserFullInfo.character_info.MaxHp));

}

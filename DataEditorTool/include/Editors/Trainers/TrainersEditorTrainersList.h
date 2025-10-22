/*****************************************************************//**
 * \file   TrainersEditorTrainersList.h
 * \brief  UiSection containing a list of all Trainer rows in the Trainers CSV file managed by its
 * parent UiTab
 *
 * \author Bennett Thomas
 * \date   October
 *********************************************************************/
#pragma once

#include "UI/UiSection.h"

class TrainersEditor;

/** 
 * \brief  UiSection containing a list of all Trainer rows in the Trainers CSV file managed by its
 * parent UiTab. 
 */
class TrainersEditorTrainersList : public UiSection
{

public:

	TrainersEditorTrainersList(TrainersEditor* InParent);

};

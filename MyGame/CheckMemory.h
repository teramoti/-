//------------------------//------------------------
// Contents(�������e) CheckMemory.h�̓��e������
//------------------------//------------------------
// user(�쐬��) Keishi Teramoto
// Created date(�쐬��) 2019 / 07/ 23
// last updated (�ŏI�X�V��) 2019 / 07/ 23
//------------------------//------------------------

#pragma once

//���o
#ifdef _DEBUG 
#ifndef DBG_NEW

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW

#endif	// _DEBUG 
#endif	// DBG_NEW

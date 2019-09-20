/*
// Dao Virtual Machine
// http://daoscript.org
//
// Copyright (c) 2006-2017, Limin Fu
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED  BY THE COPYRIGHT HOLDERS AND  CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED  WARRANTIES,  INCLUDING,  BUT NOT LIMITED TO,  THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL  THE COPYRIGHT HOLDER OR CONTRIBUTORS  BE LIABLE FOR ANY DIRECT,
// INDIRECT,  INCIDENTAL, SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES (INCLUDING,
// BUT NOT LIMITED TO,  PROCUREMENT OF  SUBSTITUTE  GOODS OR  SERVICES;  LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION)  HOWEVER CAUSED  AND ON ANY THEORY OF
// LIABILITY,  WHETHER IN CONTRACT,  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
// OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
// OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef __DAO_INFERENCER_H__
#define __DAO_INFERENCER_H__

#include"daoBase.h"


/* Instruction Node */
struct DaoInode
{
	unsigned short  code;    /* Opcode; */
	unsigned short  a, b, c; /* Operands; */
	unsigned short  state;   /* State; */
	unsigned short  level;   /* Lexical level; */
	unsigned short  line;    /* Line number in source file; */
	unsigned int    first;   /* Index of the first token of the expression; */
	unsigned short  middle;  /* The middle token, relative to "first"; */
	unsigned short  last;    /* The last token, relative to "first"; */

	unsigned int  index;   /* Index of the instruction; */

	DaoInode  *jumpTrue;
	DaoInode  *jumpFalse;
	DaoInode  *extra;

	DaoInode  *prev;
	DaoInode  *next;
};

DaoInode* DaoInode_New();

void DaoInodes_Clear( DList *inodes );

void DaoRoutine_CodesToInodes( DaoRoutine *self, DList *inodes );
void DaoRoutine_CodesFromInodes( DaoRoutine *self, DList *inodes );
void DaoRoutine_SetupSimpleVars( DaoRoutine *self );



typedef struct DaoInferencer DaoInferencer;

struct DaoInferencer
{
	unsigned char  tidHost;
	unsigned char  silent;
	unsigned char  error;

	unsigned short  currentIndex;

	DaoRoutine  *routine;
	DaoClass    *hostClass;

	DList      *inodes;
	DList      *consts;
	DList      *types;
	DList      *types2;

	DList      *rettypes;
	DList      *typeMaps;
	DList      *errors;
	DList      *array;
	DList      *array2;
	DList      *defers;
	DList      *routines;

	DMap        *defs;
	DMap        *defs2;
	DMap        *defs3;
	DMap        *rettypes2;
	DString     *mbstring;

	DaoType     *type_source;
	DaoType     *type_target;
	int          tid_target;
	int          annot_first;
	int          annot_last;

	DaoType     *basicTypes[DAO_ARRAY];
};

DaoInferencer* DaoInferencer_New();
void DaoInferencer_Delete( DaoInferencer *self );
void DaoInferencer_Init( DaoInferencer *self, DaoRoutine *routine, int silent );
void DaoInferencer_Reset( DaoInferencer *self );
int DaoInferencer_DoInference( DaoInferencer *self );

#endif

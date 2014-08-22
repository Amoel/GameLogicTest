//==============================================//
// GameLogicTest                                //
//                                              //
// Content: AnimationForm struct                //
// File:    AnimationForm.h                     //
//                                              //
// Copyright (c) 2014, Max Giller               //
//==============================================//

#pragma once

namespace GameLogicTest
{
	/* An AnimationFrame describes a segment of a spritesheet, that will be used as a single frame during the animation. */
	struct AnimationFrame
	{
		int x;
		int y;
		int width;
		int height;
	};
}
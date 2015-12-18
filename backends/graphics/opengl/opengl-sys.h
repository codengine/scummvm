/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef BACKENDS_GRAPHICS_OPENGL_OPENGL_SYS_H
#define BACKENDS_GRAPHICS_OPENGL_OPENGL_SYS_H

#include "common/scummsys.h"

#include "backends/graphics/opengl/debug.h"
#ifdef SDL_BACKEND
#include "backends/platform/sdl/sdl-sys.h"
#endif

// We allow to force GL or GLES modes on compile time.
// For this the USE_GLES_MODE define is used. The following values represent
// the given selection choices:
//  0 - Force OpenGL context
//  1 - Force OpenGL ES context
#define USE_FORCED_GL   (defined(USE_GLES_MODE) && USE_GLES_MODE == 0)
#define USE_FORCED_GLES (defined(USE_GLES_MODE) && USE_GLES_MODE == 1)

// On Tizen we include the toolchain's OpenGL file. This is something we
// actually want to avoid. However, since Tizen uses eglGetProcAddress which
// is not required to return valid function pointers to non OpenGL extension
// functions, we need the system's definitions to resolve all OpenGL
// functions.
// TODO: See if there is an alternative which allows us to avoid including
// Tizen's OpenGL header here.
#if defined(TIZEN)
	#include <FGraphicsOpengl.h>
	using namespace Tizen::Graphics::Opengl;
	#define USE_BUILTIN_OPENGL
#else
	#include "backends/graphics/opengl/opengl-defs.h"
#endif

#ifdef SDL_BACKEND
	// Win32 needs OpenGL functions declared with APIENTRY.
	// However, SDL does not define APIENTRY in it's SDL.h file on non-Windows
	// targets, thus if it is not available, we just dummy define it.
	#ifndef APIENTRY
		#define APIENTRY
	#endif
	#define GL_CALL_CONV APIENTRY
#else
	#define GL_CALL_CONV
#endif

namespace OpenGL {

enum ContextType {
	kContextGL,
	kContextGLES
};

/**
 * Description structure of the OpenGL (ES) context.
 */
struct Context {
	/** The type of the active context. */
	ContextType type;

	/**
	 * Reset context.
	 *
	 * This marks all extensions as unavailable.
	 */
	void reset(bool full = false);

	/** Whether GL_ARB_texture_non_power_of_two is available or not. */
	bool NPOTSupported;

#define GL_FUNC_DEF(ret, name, param) ret (GL_CALL_CONV *name)param
#define GL_EXT_FUNC_DEF GL_FUNC_DEF
#include "backends/graphics/opengl/opengl-func.h"
#undef GL_EXT_FUNC_DEF
#undef GL_FUNC_DEF
};

/**
 * The (active) OpenGL context.
 */
extern Context g_context;

} // End of namespace OpenGL

#define GL_CALL(x) GL_WRAP_DEBUG(g_context.x, x)

#endif

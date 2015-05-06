/*******************************************************
 * Copyright (c) 2014, ArrayFire
 * All rights reserved.
 *
 * This file is distributed under 3-clause BSD license.
 * The complete license agreement can be obtained at:
 * http://arrayfire.com/licenses/BSD-3-Clause
 ********************************************************/

#pragma once

#if defined(WITH_GRAPHICS)

#include <af/graphics.h>
#include <forge.h>

#include <map>

// default to f32(float) type
template<typename T>
GLenum getGLType();

// Print for OpenGL errors
// Returns 1 if an OpenGL error occurred, 0 otherwise.
GLenum glErrorSkip(const char *msg, const char* file, int line);
GLenum glErrorCheck(const char *msg, const char* file, int line);
GLenum glForceErrorCheck(const char *msg, const char* file, int line);

#define CheckGL(msg)      glErrorCheck     (msg, __FILE__, __LINE__)
#define ForceCheckGL(msg) glForceErrorCheck(msg, __FILE__, __LINE__)
#define CheckGLSkip(msg)  glErrorSkip      (msg, __FILE__, __LINE__)

namespace graphics
{

typedef std::map<size_t, fg::Image*> ImageMap_t;
typedef std::map<size_t, fg::Plot*> PlotMap_t;
typedef std::map<size_t, fg::Histogram*> HistogramMap_t;

typedef ImageMap_t::iterator ImgMapIter;
typedef PlotMap_t::iterator PltMapIter;
typedef HistogramMap_t::iterator HstMapIter;

class ForgeManager
{
    private:
        ImageMap_t mImgMap;
        PlotMap_t  mPltMap;
        HistogramMap_t  mHstMap;

        int mGridBoundRowId;
        int mGridBoundColId;
        std::string mGridBoundTitle;
        bool mIsGridMode;

    public:
        static fg::Window* getWindow();
        static ForgeManager& getInstance();
        ~ForgeManager();
        fg::Image* getImage(int w, int h, fg::ColorMode mode, GLenum type);
        fg::Plot* getPlot(int nPoints, GLenum type);
        fg::Histogram* getHistogram(int nBins, GLenum type);

        inline void toggleGridMode() { mIsGridMode = !mIsGridMode; }
        inline void setGridCellId(int colId, int rowId, const char* title) {
            mGridBoundRowId = rowId;
            mGridBoundColId = colId;
            mGridBoundTitle = title;
        }
        inline int cellRowId() const { return mGridBoundRowId; }
        inline int cellColId() const { return mGridBoundColId; }
        inline std::string cellTitle() const { return mGridBoundTitle; }
        inline bool isGridMode() const { return mIsGridMode; }

    protected:
        ForgeManager() {
            mIsGridMode = false;
            mGridBoundRowId = -1;
            mGridBoundColId = -1;
        }
        ForgeManager(ForgeManager const&);
        void operator=(ForgeManager const&);
        void destroyResources();
};

}

#endif

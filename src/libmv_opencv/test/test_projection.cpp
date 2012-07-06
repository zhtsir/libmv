/*
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2009, Willow Garage, Inc.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of Willow Garage, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "test_precomp.hpp"
#include "opencv2/sfm/sfm.hpp"

using namespace cv;
using namespace std;

TEST(Sfm_HomogeneousToEuclidean, correctness)
{
    Matx33f X(1, 2, 3,
              4, 5, 6,
              2, 1, 0);

    Matx23f XEuclidean;
    HomogeneousToEuclidean(X,XEuclidean);

    EXPECT_EQ( X.rows-1, XEuclidean.rows );

    for(int y=0;y<X.rows-1;++y)
        for(int x=0;x<X.cols;++x)
            if (X(X.rows-1,x)!=0)
                EXPECT_LE( std::abs(X(y,x)/X(X.rows-1, x) - XEuclidean(y,x)), 1e-4 );
}

TEST(Sfm_EuclideanToHomogeneous, correctness)
{
    Matx33f x(1, 2, 3,
              4, 5, 6,
              2, 1, 0);

    Matx43f XHomogeneous;
    EuclideanToHomogeneous(x,XHomogeneous);

    EXPECT_EQ( x.rows+1, XHomogeneous.rows );

    for(int i=0;i<x.cols;++i)
        EXPECT_EQ( 1, XHomogeneous(x.rows,i) );
}
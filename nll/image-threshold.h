/*
 * Numerical learning library
 * http://nll.googlecode.com/
 *
 * Copyright (c) 2009-2012, Ludovic Sibille
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Ludovic Sibille nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY LUDOVIC SIBILLE ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE REGENTS AND CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef NLL_IMAGE_THRESHOLD
# define NLL_IMAGE_THRESHOLD

# include "image.h"

# pragma warning( push )
# pragma warning( disable:4244 ) // conversion from 'const double' to XXX, possible loss of data

namespace nll
{
namespace core
{
   /**
    @ingroup core
    @brief Define a threshold operator (greater).
    */
   template <class T>
	class ThresholdGreater
	{
	public:
      /**
       @brief sets the threshold
       */
		ThresholdGreater(T threshold) : _threshold(threshold){}

      /**
       @return true if above the threshold
       */
		bool operator()(T test) const {return test > _threshold;}
	private:
		T			_threshold;
	};

   /**
    @ingroup core
    @brief Define a threshold operator (lower).
    */
	template <class T>
	class ThresholdLower
	{
	public:
      /**
       @brief sets the threshold
       */
		ThresholdLower(T threshold) : _threshold(threshold){}

      /**
       @return true if below the threshold
       */
		bool operator()(T test) const {return test < _threshold;}
	private:
		T			_threshold;
	};

   /**
    @ingroup core
    @brief Define a threshold operator (between).
    */
	template <class T>
	class ThresholdBetween
	{
	public:
      /**
       @brief sets the 2 thresholds
       */
		ThresholdBetween(T min, T max) : _min(min), _max(max){}

      /**
       @return true if it is inbetween
       */
		bool operator()(T test) const {return test >= _min && test <= _max;}
	private:
		T			_min;
		T			_max;
	};

   /**
    @ingroup core
    @brief Define a sum agregator.
    
    Tt computes the sum of  the pixel components. It is used to parametrized the threshold
    @sa threshold_generic
    */
	template <class type>
	struct AgregatorSum
	{
		static typename BiggerType<type>::type op(type* buf, size_t nbComp)
		{
			typename BiggerType<type>::type tmp = 0;
			for (size_t n = 0; n < nbComp; ++n)
				tmp += buf[n];
			return static_cast<typename BiggerType<type>::type> (tmp / nbComp);
		}
	};

   /**
    @ingroup core
    @brief Thresold an image.
    
    If ( Thresold(x, y) ) then we keep the pixel, else it is replaced by the background value
    @example threshold<ui8, Mapper, ThresholdLower<ui8>, AgregatorSum<ui8> >(image, mat::ThresholdLower<ui8>(127));
    */
	template <class type, class mapper, class allocator, class Threshold, class Agregator>
	void threshold_generic(Image<type, mapper, allocator>& image, const Threshold& thr, const type* background = Image<type, mapper, allocator>::black())
	{
		Image<type, mapper, allocator> tmp(image.sizex(), image.sizey(), image.getNbComponents(), false, image.getAllocator());
		for (size_t y = 0; y < image.sizey(); ++y)
			for (size_t x = 0; x < image.sizex(); ++x)
			{
				type* t1 = image.point(x, y);
				type* t2 = tmp.point(x, y);
				typename BiggerType<type>::type tt = Agregator::op(t1, image.getNbComponents());
				if (thr(tt))
					for (size_t c = 0; c < image.getNbComponents(); ++c)
						t2[c] = t1[c];
				else
					for (size_t c = 0; c < image.getNbComponents(); ++c)
						t2[c] = background[c];
			}
		image = tmp;
	}

   /**
    @ingroup core
    @brief Thresold an image using a sum agregator.
    @sa AgregatorSum
    */
	template <class type, class mapper, class allocator, class Threshold>
	void threshold(Image<type, mapper, allocator>& image, const Threshold& thr, const type* background = Image<type, mapper, allocator>::black())
	{
		threshold_generic<type, mapper, allocator, Threshold, AgregatorSum<type> >(image, thr, background);
	}


   /**
    @ingroup core
    @brief binarize an image according to a thresold.

    If threshold(x, y ) then the pixel (x, y ) is set to foreground else background
    */
	template <class type, class mapper, class allocator, class Threshold, class Agregator>
	void binarize_generic(Image<type, mapper, allocator>& image, const Threshold& thr, const type* background = Image<type, mapper, allocator>::black(), const type* foreground = Image<type, mapper, allocator>::white())
	{
		Image<type, mapper, allocator> tmp(image.sizex(), image.sizey(), image.getNbComponents(), false, image.getAllocator());
		for (size_t y = 0; y < image.sizey(); ++y)
			for (size_t x = 0; x < image.sizex(); ++x)
			{
				type* t1 = image.point(x, y);
				type* t2 = tmp.point(x, y);
				typename BiggerType<type>::type tt = Agregator::op(t1, image.getNbComponents());
				if (thr(tt))
					for (size_t c = 0; c < image.getNbComponents(); ++c)
						t2[c] = foreground[c];
				else
					for (size_t c = 0; c < image.getNbComponents(); ++c)
						t2[c] = background[c];
			}
		image = tmp;
	}

   /**
    @ingroup core
    @brief binarize an image according to a thresold using a sum agregator.

    If threshold(x, y ) then the pixel (x, y ) is set to foreground else background
    */
	template <class type, class mapper, class allocator, class Threshold>
	void binarize(Image<type, mapper, allocator>& image, const Threshold& thr, const type* background = Image<type, mapper, allocator>::black(), const type* foreground = Image<type, mapper, allocator>::white())
	{
		binarize_generic<type, mapper, allocator, Threshold, AgregatorSum<type> >(image, thr, background, foreground);
	}
}
}

#pragma warning( pop )

#endif

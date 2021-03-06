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

#ifndef NLL_IMAGING_VOLUME_BARYCENTRE_H_
# define NLL_IMAGING_VOLUME_BARYCENTRE_H_

namespace nll
{
namespace imaging
{
   /**
    @ingroup imaging
    @brief Computes the barycentre of the volume, using this specific LUT in voxel space
    @param lut the LUT to use. Only the first component will be used, equivalent as computing the barycenter of the transformed LUT volume
    */
   template <class T, class Buffer, class Lut>
   core::vector3f computeBarycentreVoxel( const imaging::Volume<T, Buffer>& vol, const Lut& lut )
   {
      // compute the barycentre
      float nb = 0;
      const size_t lutSize = lut.getSize();
      core::vector3f tmp( 0, 0, 0 );
      for ( size_t z = 0; z < vol.sizez(); ++z )
      {
         for ( size_t y = 0; y < vol.sizey(); ++y )
         {
            for ( size_t x = 0; x < vol.sizex(); ++x )
            {
               const float value = vol( x, y, z );
               const float computed = lut.transform( value )[ 0 ] / lutSize;  // to avoid overflow. Since we must divide by the sum, we can divide by a constant!
                                                                              // use the actual LUT value and not the index so that we can do non linear mappings
               tmp += core::vector3f( static_cast<f32>( x ),
                                      static_cast<f32>( y ), 
                                      static_cast<f32>( z ) ) * computed;
               nb += computed;
            }
         }
      }
      if ( nb <= 0 )
      {
         // no voxel visible, so just return the volume origin
         return core::vector3f( 0, 0, 0 );
      }
      tmp /= nb;

      {
         std::stringstream ss;
         ss << "computeBarycentreVoxel:" << std::endl;
         ss << " index=" << tmp << std::endl;
         core::LoggerNll::write( core::LoggerNll::IMPLEMENTATION, ss.str() );
      }

      return tmp;
   }

   /**
    @ingroup imaging
    @brief Computes the barycentre of the volume, using this specific LUT
    @param lut the LUT to use. Only the first component will be used, equivalent as computing the barycenter of the transformed LUT volume
    */
   template <class T, class Buffer, class Lut>
   core::vector3f computeBarycentre( const VolumeSpatial<T, Buffer>& vol, const Lut& lut )
   {
      // by default, it is the centre of the volume
      const core::VolumeGeometry geometry( vol.getPst() );
      const core::vector3f position = geometry.indexToPosition( computeBarycentreVoxel( vol, lut ) );

      {
         std::stringstream ss;
         ss << "Compute barycenter:" << std::endl;
         vol.print( ss );
         ss << " position MM=" << position;
         core::LoggerNll::write( core::LoggerNll::IMPLEMENTATION, ss.str() );
      }

      return position;
   }
}
}

#endif
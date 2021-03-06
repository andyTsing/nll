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

#ifndef NLL_IMAGING_VOLUME_IO_BIN_H_
# define NLL_IMAGING_VOLUME_IO_BIN_H_

#define NLL_IMAGING_BINARY_VOLUME_READER_VERSION   0x12000001

namespace nll
{
namespace imaging
{
   /**
    @ingroup imaging
    @brief Export a spatial volume to a stream
    @note 2 files are actually exported: the binary data and a TXT header.
          The format is the following:
          header: version
                  size
                  background color
                  PST
          binary: line by line, and slice by slice

          T must be a POD

    @param f the name of the file. `f`.hdr and `f`.bin will be created
    */ 
   template <class T, class Storage>
   bool writeVolumeBinary( const VolumeSpatial<T, Storage>&  volume, const std::string& f )
   {
      std::ofstream hdr( ( f + ".hdr" ).c_str() );
      std::ofstream bin( ( f + ".bin" ).c_str(), std::ios::binary );
      if ( hdr.eof() || bin.eof() )
         return false;

      // header
      hdr << "version:" << NLL_IMAGING_BINARY_VOLUME_READER_VERSION << std::endl;
      hdr << "size:" << volume.getSize()[ 0 ] << " " << volume.getSize()[ 1 ] << " " << volume.getSize()[ 2 ] << std::endl;
      hdr << "background:" << volume.getBackgroundValue() << std::endl;
      for ( size_t ny = 0; ny < 4; ++ny )
      {
         for ( size_t nx = 0; nx < 4; ++nx )
         {
            hdr << volume.getPst()( ny, nx );
            if ( nx != 3 )
               hdr << " ";
         }
         hdr << std::endl;
      }

      // binary
      for ( size_t z = 0; z < volume.sizez(); ++z )
      {
         for ( size_t y = 0; y < volume.sizey(); ++y )
         {
            for ( size_t x = 0; x < volume.sizex(); ++x )
            {
               const T val = volume( x, y, z );
               bin.write( (const char*)&val, sizeof( T ) );
            }
         }
      }

      return true;
   }

   /**
    @ingroup imaging
    @brief Read a volume from a header file and a data file
    */
   template <class T, class Storage>
   bool readVolumeBinary( VolumeSpatial<T, Storage>&  volume, const std::string& f )
   {
      std::ifstream hdr( ( f + ".hdr" ).c_str() );
      std::ifstream bin( ( f + ".bin" ).c_str(), std::ios::binary );
      if ( hdr.eof() || bin.eof() )
         return false;

      std::string line;

      //
      // read header
      //

      // get the version
      std::getline( hdr, line );
      std::vector<const char*> lineSpt = core::split( line, ':' );
      if ( lineSpt.size() != 2 )
         throw std::runtime_error( "error: can't parse volume header: version" );

      size_t version = atoi( lineSpt[ 1 ] );
      if ( version != NLL_IMAGING_BINARY_VOLUME_READER_VERSION )
         throw std::runtime_error( "error: header version not recognized" );

      // get size
      std::getline( hdr, line );
      lineSpt = core::split( line, ':' );
      if ( lineSpt.size() != 2 )
         throw std::runtime_error( "error: can't parse volume header: size" );
      std::string sizeStr( lineSpt[ 1 ] );
      lineSpt = core::split( sizeStr, ' ' );
      if ( lineSpt.size() != 3 )
         throw std::runtime_error( "error: volume header's size is malformed" );
      core::vector3ui size( atoi( lineSpt[ 0 ] ), atoi( lineSpt[ 1 ] ), atoi( lineSpt[ 2 ] ) );

      // get background
      T background;
      std::stringstream ss;
      
      std::getline( hdr, line );
      lineSpt = core::split( line, ':' );
      if ( lineSpt.size() != 2 )
         throw std::runtime_error( "error: can't parse volume header: background" );
      ss << lineSpt[ 1 ];
      ss >> background;

      // get PSR
      typename VolumeSpatial<T, Storage>::Matrix tfm( 4, 4 );
      for ( size_t y = 0; y < 4; ++y )
      {

         std::getline( hdr, line );
         lineSpt = core::split( line, ' ' );
         if ( lineSpt.size() != 4 )
            throw std::runtime_error( "error: can't parse volume header: transformation matrix" );
         for ( size_t x = 0; x < 4; ++x )
         {
            tfm( y, x ) = static_cast<typename VolumeSpatial<T, Storage>::Matrix::value_type>( atof( lineSpt[ x ] ) );
         }
      }
   
      //
      // read binary data
      //
      volume = VolumeSpatial<T, Storage>( size, tfm );
      for ( size_t z = 0; z < volume.sizez(); ++z )
      {
         for ( size_t y = 0; y < volume.sizey(); ++y )
         {
            for ( size_t x = 0; x < volume.sizex(); ++x )
            {
               if ( bin.eof() )
                  throw std::runtime_error( "error: read all data of the volume" );
               T val;
               bin.read( (char*)&val, sizeof( T ) );
               volume( x, y, z ) = val;
            }
         }
      }
      return true;
   }
}
}

#endif
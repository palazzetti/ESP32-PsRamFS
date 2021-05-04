/*\

  MIT License

  Copyright (c) 2021-now tobozo

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.

\*/

#ifndef _PFS_H_
#define _PFS_H_

#ifdef __cplusplus
extern "C" {
#endif



/**
 *Configuration structure for esp_vfs_pfs_register.
 */
typedef struct {
    const char *base_path;            /**< Mounting point. */
    const char *partition_label;      /**< Label of partition to use. */
    uint8_t format_if_mount_failed:1; /**< Format the file system if it fails to mount. */
    uint8_t dont_mount:1;             /**< Don't attempt to mount or format. Overrides format_if_mount_failed */
} esp_vfs_pfs_conf_t;


typedef struct
{
  int file_id;
  char * name;
  char * bytes;
  unsigned long size;
  unsigned long memsize;
  unsigned long index;
} pfs_file_t;


typedef struct
{
  int dir_id;
  char * name;
} pfs_dir_t;


typedef struct pfs_stat_t
{
  unsigned int  st_mode;
  unsigned long st_mtime;
  unsigned long st_size;
  const char*   st_name;
} pfs_stat_t;


typedef enum {
  pfs_seek_set = 0,
  pfs_seek_cur = 1,
  pfs_seek_end = 2
} pfs_seek_mode;


pfs_file_t ** pfs_get_files();
pfs_dir_t  ** pfs_get_dirs();
int         pfs_max_items();
void        pfs_free();
void        pfs_clean_files();
int         pfs_stat( const char * path, const void *_stat );
pfs_file_t* pfs_fopen( const char * path, const char* mode );
size_t      pfs_fread( uint8_t *buf, size_t size, size_t count, pfs_file_t * stream );
size_t      pfs_fwrite( const uint8_t *buf, size_t size, size_t count, pfs_file_t * stream);
int         pfs_fflush(pfs_file_t * stream);
int         pfs_fseek( pfs_file_t * stream, long offset, pfs_seek_mode mode );
size_t      pfs_ftell( pfs_file_t * stream );
void        pfs_fclose( pfs_file_t * stream );
int         pfs_unlink( const char * path );
int         pfs_rename( const char * from, const char * to );
pfs_dir_t*  pfs_opendir( const char * path );
int         pfs_mkdir( const char* path );
struct dirent * pfs_readdir( pfs_dir_t * dir );
void        pfs_closedir( pfs_dir_t * dir );
void        pfs_rewinddir( pfs_dir_t * dir );
esp_err_t esp_vfs_pfs_register(const esp_vfs_pfs_conf_t *conf);

#ifdef __cplusplus
}
#endif

#endif

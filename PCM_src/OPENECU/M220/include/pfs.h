/*****************************************************************************/
/**
 *  \file    pfs.h
 *  \brief   Exported interfaces for non-volatile filesystem feature
 *
 *  Version: $Id: pfs.h 31475 2012-11-13 20:49:25Z sborders $
 *  File:    $URL: https://apple.ps.local/svn/OpenECU/development/platform/tags/release-2.2.1-igloo-dev4/targets/src/common/pfs/pfs.h $
 */

/*  Copyright (C) 2010-2012 Pi Innovo
 *  This document (program) contains proprietary information
 *  which is the property of Pi Innovo
 *  The contents of this document (program) must not be copied
 *  or disclosed to a third party without the prior agreement
 *  of an authorised officer of Pi Innovo
 */

#ifndef PFS_H
#define PFS_H

#if (!defined(CFG_G850)) || (defined(CFG_DOXYGEN))
/* Those targets not currently supported by PFS but this header file still in C-API collection */

/********* Includes *********/

#include "psy.h"

/********* These macros can be changed *********/

/** Internal platform use only. Indicates that we don't know
 *  the type of the file being considered.
 */
#define PFS_FTYPE_UNKNOWN       0x10000

/** File IDs with this bit set are reserved for platform use.
 *  User applications may not write or delete such files.
 *
 * \ingroup c_interface
 */
#define PFS_FTYPE_PLATFORM       0x8000

/** The use of this bit in file IDs is reserved for future use.
 *  User applications may not write or delete files with this
 *  bit set in the file ID.
 *
 * \ingroup c_interface
 */
#define PFS_FTYPE_RESERVED       0x4000

/** The use of this bit in file IDs indicates a file which must
 *  not be deleted in any future 'delete all' operation. User applications
 *  may create files with this ID set. A specific request to delete
 *  such a file will succeed however.
 *
 * \ingroup c_interface
 */
#define PFS_FTYPE_READONLY       0x2000

/** Build timestamps as returned by pfs_fstat()
 * are stored in a compressed format. A
 * zero value corresponds to 00:00 on 1 January of this year.
 *
 * \ingroup c_interface
 */
#define PFS_ORIGIN_YEAR           2010

/** Maximum year allowed for build timestamps.
 */
#define PFS_MAX_YEAR              2099

/** Build timestamps as returned by pfs_fstat()
 *  are stored in a compressed format. This constant defines
 *  the resolution of the timestamp values.
 *
 * \ingroup c_interface
 */
#define PFS_DATESTAMP_SEC_PER_BIT  180

/********* These macros must not be changed *********/

/* None */

/********* Global Structure Definitions *********/

/** Set of return codes for all pfs exported functions.
 *
 * Each pfs function returns PFS_RC_OK to indicate success,
 * and may return one or more of the other values to indicate
 * a failure to process the desired command.
 */
typedef enum
{
    /** Returned to indicate success.
     *
     * \ingroup c_interface
     */
    PFS_RC_OK,

    /** General purpose return code to indicate failure.
     *
     * \ingroup c_interface
     */
    PFS_RC_ERROR,

    /** An operation was requested for a file which does
     *  does not currently exist in the filesystem.
     *
     * \ingroup c_interface
     */
    PFS_RC_NO_SUCH_FILE,

    /** A value was provided that was out of range for the
     *  requested operation.
     *
     * \ingroup c_interface
     */
    PFS_RC_OUT_OF_RANGE,

    /** An operation was requested on a file ID reserved for
     *  platform use.
     *
     * \ingroup c_interface
     */
    PFS_RC_FILE_DISALLOWED,

    /** A checksum operation detected invalid data.
     */
    PFS_RC_CHECKSUM_INVALID,

    /** An erased area of memory was found.
     */
    PFS_RC_BLANK,

    /** A flash operation was left pending by this operation.
     */
    PFS_RC_PENDING
}
PFS_RC_T;

/** Error values for debugging -- when an error is found in a call to the PFS
 * API, the feature calls a function with an enumeration from this type.
 *
 * \ingroup  c_interface
 */
typedef enum
{
    /** Error raised if the PGN requested function finds an invalid function
     * argument.
     */
    PFS_ECC_ERROR_DURING_FLASH_OP        = 1,

    /** Error raised if the PG receive function finds an invalid function
     * argument.
     */
    PFS_RUNTIME_CORRUPT_FILE_FOUND       = 2
}
PFS_ERROR_T;

/** The type used to store file revision (version) number. Revision
 *  numbers eventually wrap around to zero and start counting up
 *  again from there. The revision number applies to the whole filesystem
 *  (similar to the use in the Subversion system). See also pfs_is_newer().
 *
 * \ingroup c_interface
 */
typedef U16 PFS_REVISION_T;

/** The type used to represent a file ID (equivalent to a filename,
 *  but simply a compact numerical type).
 *
 * \ingroup c_interface
 */
typedef U16 PFS_FILE_ID_T; /* compact but too short to be meaningful ASCII really */

/** Structure which conveys statistical information about the
 *  current status of the non-volatile filesystem.
 *
 *  See also pfs_get_filesystem_stats().
 */
typedef struct
{
    /** The total raw space available for file storage. This
     *  includes the overhead of storing metadata and padding,
     *  but does not include the duplication of space in different
     *  flash memory blocks.
     *
     * Range: [0, 262143] bytes
     *
     * \ingroup c_interface
     */
    S32            byte_capacity;

    /** The total raw space currently used by files, metadata
     *  and padding.
     *
     * Range: [0, 262143] bytes
     *
     * \ingroup c_interface
     */
    S32            bytes_used;

    /** The total raw space allocated to the non-volatile filesystem,
     *  summing all the space in the flash memory blocks allocated to it.
     *
     * Range: [0, 262143] bytes
     *
     * \ingroup c_interface
     */
    S32            bytes_total_size;

    /** The total space which has been found to contain invalid data
     *  or for which flash programming operations failed. This is reset to
     *  zero on power-up, and then any invalid data found already present
     *  in the system contributes to this total before any file writes
     *  are attempted.
     *
     * Range: [0, 262143] bytes
     *
     * \ingroup c_interface
     */
    S32            bytes_bad;

    /** The total number of times that a flash erase operation has been
     *  started on any block allocated to the filesystem.
     *
     * Range: [0, 16777215] erases
     *
     * \ingroup c_interface
     */
    U32            lifetime_erases;

    /** The revision number of the most recent event (file write, delete,
     *  erase etc) that has been attempted in the filesystem.
     *
     * Range: [0, 65535]
     *
     * \ingroup c_interface
     */
    PFS_REVISION_T head_revision;

    /** The number of valid, completely written files currently present
     *  in the filesystem belonging to the application.
     *
     * Range: [0, max_files]
     *
     * \ingroup c_interface
     */
    S16            user_files;

    /** The number of valid, completely written files currently present
     *  in the filesystem with platform-reserved IDs.
     *
     * Range: [0, max_files]
     *
     * \ingroup c_interface
     */
    S16            platform_files;

    /** The total number of valid, completely written files currently present
     *  in the filesystem.
     *
     * Range: [0, max_files]
     *
     * \ingroup c_interface
     */
    S16            total_files;

    /** The number of times since the most recent power-on that
     *  the system failed to successfully write a file.
     *
     * Range: [0, 32767]
     *
     * \ingroup c_interface
     */
    S16            failed_writes;

    /** The number of times since the most recent power-on that
     *  the system ignored a file it found on disk because
     *  its directory space was already full. As different versions
     *  of the file may be found on disk, this may be larger than
     *  the number of unique files which were discarded.
     *
     * Range: [0, 32767]
     *
     * \ingroup c_interface
     */
    S16            discarded_files;

    /** The number of files that have been detected by runtime
     *  processing to be corrupt since power-on.
     *
     * Range: [0, 32767]
     *
     * \ingroup c_interface
     */
    S16            runtime_corrupt_files;

    /** The number of separate flash memory blocks used by the
     *  filesystem to achieve redundant storage.
     *
     * Range: [2, 7]
     *
     * \ingroup c_interface
     */
    S8             blocks;

    /** The zero-based index of the flash memory block to which
     *  file writes are currently being made.
     *
     * Range: [0, 7]
     *
     * \ingroup c_interface
     */
    S8             active_block_idx;
}
PFS_FILESYS_STATS_T;

/** Structure which conveys statistical information about the
 *  current status of one file in the filesystem.
 *
 *  Except where stated otherwise, each statistic refers to the
 *  file already stored on disk, and not to any new version for
 *  which a write operation is in progress.
 *
 *  See also pfs_fstat().
 */
typedef struct
{
    /** The size of the actual useful data contained in the file,
     *  excluding any overhead or padding.
     *
     * Range: [0, 262143] bytes
     *
     * \ingroup c_interface
     */
    S32            size_bytes;

    /** The size of flash memory consumed by this file in the
     *  filesystem, including metadata overhead and any padding.
     *
     * Range: [0, 262143] bytes
     *
     * \ingroup c_interface
     */
    S32            disk_bytes;

    /** The timestamp of the application software build responsible
     *  for the last write of this file.
     *
     *  See also PFS_DATESTAMP_SEC_PER_BIT and PFS_ORIGIN_YEAR.
     *
     * Range: [0, 16777215]
     *
     * \ingroup c_interface
     */
    U32            encoded_build_time;

    /** The revision number of the file stored in the system.
     *
     * Range: [0, 65535]
     *
     * \ingroup c_interface
     */
    PFS_REVISION_T revision;

    /** Data provided by the client when the file was written. This
     *  can be used for example to define a use-specific layout
     *  version, such that the client can interpret old files correctly
     *  if the format has changed. This is kept separate from the
     *  actual file data to allow that to consist of equal-sized
     *  records (see pfs_fwrite_simple_queue()).
     *
     * Range: [0, 65535]
     *
     * \ingroup c_interface
     */
    U16            user_data;

    /** The major version number of the application software build
     *  responsible for the last write of this file, e.g.
     *  "2" in version "2.7.13".
     *
     * Range: [0, 255]
     *
     * \ingroup c_interface
     */
    U8             app_ver_major;

    /** The minor version number of the application software build
     *  responsible for the last write of this file, e.g.
     *  "7" in version "2.7.13".
     *
     * Range: [0, 255]
     *
     * \ingroup c_interface
     */
    U8             app_ver_minor;

    /** The sub-minor version number of the application software build
     *  responsible for the last write of this file, e.g.
     *  "13" in version "2.7.13".
     *
     * Range: [0, 255]
     *
     * \ingroup c_interface
     */
    U8             app_ver_subminor;

    /** Whether this file is already safely stored in the filesystem.
     *  For a new file, this becomes TRUE when the write process has
     *  completed.
     *
     * \ingroup c_interface
     */
    BOOL           on_disk;

    /** Whether this file has a write or delete operation queued or
     *  in progress.
     *
     * \ingroup c_interface
     */
    BOOL           write_queued;

    /** Whether this file was written by software matching the build
     *  timestamp of the currently executing application software.
     *
     * \ingroup c_interface
     */
    BOOL           this_build_wrote;

    /** Whether this file was written by software matching the build
     *  version (e.g. "2.3.17") of the currently executing application
     *  software.
     *
     * \ingroup c_interface
     */
    BOOL           this_ver_wrote;
}
PFS_FILE_STATS_T;

/** Used to track current state of a file write or delete operation.
 *  File writes and deletes are handled in steps by the periodic routine,
 *  which traverses through a state machine for each one.
 */
typedef enum
{
    /** Waiting in queue, no action performed yet.
     */
    PFS_FILE_NOT_STARTED,

    /** File/delete record metadata header write due or started.
     */
    PFS_FILE_AWAITING_HEADER_WRITE,

    /** File/delete record header flash program in progress.
     */
    PFS_FILE_HEADER_WRITE_IN_PROGRESS,

    /** File/delete record header flash program buffer flush in progress.
     */
    PFS_FILE_HEADER_COMPLETE_REQUESTED,

    /** File/delete record metadata header verification due or in progress.
     */
    PFS_FILE_VERIFYING_HEADER,

    /** File is in the process of being written chunk by chunk.
     */
    PFS_FILE_WRITING_CHUNKS,

    /** Waiting for closing flash programming operation.
     */
    PFS_FILE_AWAITING_PROG_COMPLETE,

    /** Post-write checksum of file is in progress.
     */
    PFS_FILE_VERIFYING,

    /** Some error occurred in writing the file and we need to
     *  account for the lost disk space
     */
    PFS_FILE_WRITE_FAILED,

    /** Some error occurred in writing the file; we have already
     *  accounted for any lost disk space, but need to update statistics
     *  before discarding this entry from the queue.
     */
    PFS_COMPLETE_FAILED_STATS,

    /** All operations complete for this file operation (whether or not
     *  it was successful).
     */
    PFS_FILE_WRITE_COMPLETE
}
PFS_FILE_STATUS_T;

/** The kind of operation (present in the queue of waiting operations).
 */
typedef enum
{
    /** Unused queue entry.
     */
    PFS_NO_ENTRY,

    /** A "simple" file write (i.e. to write a complete file based on
     *  a provided contiguous area of memory).
     *
     *  In future, a "complex" write may be supported to allow file
     *  append, insert or truncate operations without the file having
     *  to be buffered in RAM.
     */
    PFS_WRITE_SIMPLE,

    /** Like a simple write, but done internally by this feature to
     *  move a file from one flash block to another.
     */
    PFS_FILE_CONSOLIDATION_COPY,

    /** A file deletion.
     */
    PFS_FILE_DELETE
}
PFS_WRITE_TYPE_T;

/** All of the data required to process a queued operation (file write
 *  or delete etc) as it progresses through the required stages.
 */
typedef struct
{
    /** The next place in memory from which application data should be read.
     */
    const U8*              next_src_ptr;

    /** The next place in flash memory to which file data should be written,
     *  or NULL if not yet allocated.
     */
    const U8*              next_dest_ptr;

    /** The first location in flash memory to which data is written for
     *  this file or delete record (including the standard header).
     */
    const U8*              base_dest_ptr;

    /** The useful data size of the file (not including any overheads).
     */
    S32                    total_content_len;

    /** The amount of useful data still waiting to be written or verified.
     */
    S32                    remaining_content_len;

    /** The increase in disk usage which results from processing this operation
     *  successfully. If the operation fails, we are left with whatever valid
     *  data we previously had, so there is no change in usage.
     */
    S32                    disk_use_change_on_write;

    /** The amount of file-specific metadata still to write (not including the
     *  standard header record; only that which is specific to file records).
     */
    S16                    remaining_metadata_len;

    /** The ID of the file to be written or deleted.
     */
    PFS_FILE_ID_T          file_id;

    /** The current state of the operation sequence being worked through for
     * this entry.
     */
    PFS_FILE_STATUS_T      state;

    /** Used to maintain a checksum of the file as it is programmed or verified.
     */
    U16                    crc16;

    /** Client data used for their own purposes, kept out of bulk
     *  file data to allow that to consist of equal-sized records.
     *  Used for things like format/layout version of file.
     */
    U16                    user_data;

    /** The smallest units to copy at a time from the client source.
     */
    S16                    coherent_copy_size;

    /** What sort of operation this is (see typedef for this element).
     */
    PFS_WRITE_TYPE_T       type;

    /** Whether another process has requested we abort this write.
     */
    BOOL                   abort;

    /** Remaining size of file checksum to write
     */
    S8                     remaining_crc_len;
}
PFS_FILE_WRITE_ENTRY_T;

/** Type used to remember the location in flash memory of a file.
 *
 *  A compact type is used because there may be a need to store a
 *  large number of files, and we do not want the RAM file directory
 *  to become very large.
 *
 * Detailed description of enumeration here if applicable.
 */
typedef U16 PFS_LOCATION_T;

/** RAM data stored for each unique file.
 *
 * As file metadata is all in flash, we only really need
 * to remember where in flash to look for each file.
 */
typedef struct
{
    /** Identifies where this file currently resides in flash. The location
     *  is packed into a smaller type so that the directory of files does
     *  not get too large if an application needs many files.
     */
    PFS_LOCATION_T location;

    /* Do not need anything else, as all the other file information is in flash.
     * However, we could add a 'last written in this power cycle' time here if
     * we ever wanted to automatically handle files not being rewritten too
     * frequently, or even automatic periodic writes.
     */
}
PFS_FILE_DIR_ENTRY_T;


/********* Global Variables *********/

/** The number of different file write/delete operations that can be simultaneously
 *  queued.
 */
extern const U16 pfs_write_queue_size;

/** Maximum number of simultaneous platform-owned files supported:
 */
extern const U16 pfs_max_num_platform_files;

/** Maximum number of simultaneous application-specific files supported.
 *  This is currently fixed, but could in future be a C-API specified item
 *  to support applications that need to write a large number of different
 *  files.
 *
 * \ingroup c_interface
 */
extern const U16 pfs_max_num_user_files;

/** The queue of operations to process; see typedef definition
 *  for more.
 */
extern volatile PFS_FILE_WRITE_ENTRY_T pfs_write_queue[];

/** Directory of files currently present in the system, maintained
 *  in order sorted by ascending file ID. See typedef definition
 *  for more.
 */
extern volatile PFS_FILE_DIR_ENTRY_T pfs_directory[];

/********* Global Prototypes *********/

extern PFS_RC_T pfs_fread
(
    PFS_FILE_ID_T pfsf_file_id,
    U32           pfsf_byte_offset,
    U8*           pfsf_dest_ptr,
    U32           pfsf_max_bytes,
    U32*          pfsf_actual_bytes
);

extern PFS_RC_T pfs_fstat
(
    PFS_FILE_ID_T     pfsf_file_id,
    PFS_FILE_STATS_T* pfsf_file_stats
);

extern PFS_RC_T pfs_fdelete_queue
(
    PFS_FILE_ID_T pfsf_file_id
);

extern PFS_RC_T pfs_fwrite_queue
(
    PFS_FILE_ID_T pfsf_file_id,
    const U8*     pfsf_src_ptr,
    S32           pfsf_byte_len,
    U16           pfsf_user_data,
    S16           pfsf_coherent_copy_size
);

extern PFS_RC_T pfs_get_filesystem_stats
(
    PFS_FILESYS_STATS_T* pfsf_stats
);

extern void pfs_flush_all
(
    void
);

extern PFS_RC_T pfs_get_file_id_by_idx
(
    U16            pfsf_file_idx,
    PFS_FILE_ID_T* pfsf_file_id_ptr
);

extern BOOL pfs_is_newer
(
    PFS_REVISION_T pfsf_old_revision,
    PFS_REVISION_T pfsf_new_revision
);

extern void pfs_lock_filesystem
(
    void
);

extern void pfs_unlock_filesystem
(
    void
);

extern U32 pfs_encode_time
(
    U16 pfsf_sec,
    U16 pfsf_min,
    U16 pfsf_hour,
    U16 pfsf_day,
    U16 pfsf_month,
    U16 pfsf_year
);

extern void pfs_client_task
(
    void
);

/* Possible future enhancements:
 *  A write function that allows the client to specify the origin and size of
 *  the beginning, middle and end of a new file, each in terms of either a
 *  source pointer and length, or an offset into the (existing) file and
 *  length. This would allow file truncation, insertion, append, and mid-
 *  deletion, all without having to buffer the entire file in RAM.
 *
 *  A function to abort write in progress.
 *
 *  Delete all files depending on reported build or app version.
 *
 *  Lock filesystem only if file of specified ID is being written now,
 *  to avoid awkward client logic and avoid unnecessary resource locking
 *  overhead.
 *
 *  A function to decode build timestamp values.
 */

/********* Global Variables *********/

/* None */

#endif /* not an unsupported target for PFS */

#endif /* PFS_H */

/* -*- c-file-style: "ruby" -*- */
/*
  Copyright (C) 2009  Kouhei Sutou <kou@clear-code.com>

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "rb-groonga-private.h"

VALUE rb_eGrnError;

static VALUE eGrnEndOfData;
static VALUE eGrnUnknownError;
static VALUE eGrnOperationNotPermitted;
static VALUE eGrnNoSuchFileOrDirectory;
static VALUE eGrnNoSuchProcess;
static VALUE eGrnInterruptedFunctionCall;
static VALUE eGrnInputOutputError;
static VALUE eGrnNoSuchDeviceOrAddress;
static VALUE eGrnArgListTooLong;
static VALUE eGrnExecFormatError;
static VALUE eGrnBadFileDescriptor;
static VALUE eGrnNoChildProcesses;
static VALUE eGrnResourceTemporarilyUnavailable;
static VALUE eGrnNotEnoughSpace;
static VALUE eGrnPermissionDenied;
static VALUE eGrnBadAddress;
static VALUE eGrnResourceBusy;
static VALUE eGrnFileExists;
static VALUE eGrnImproperLink;
static VALUE eGrnNoSuchDevice;
static VALUE eGrnNotADirectory;
static VALUE eGrnIsADirectory;
static VALUE eGrnInvalidArgument;
static VALUE eGrnTooManyOpenFilesInSystem;
static VALUE eGrnTooManyOpenFiles;
static VALUE eGrnInappropriateIOControlOperation;
static VALUE eGrnFileTooLarge;
static VALUE eGrnNoSpaceLeftOnDevice;
static VALUE eGrnInvalidSeek;
static VALUE eGrnReadOnlyFileSystem;
static VALUE eGrnTooManyLinks;
static VALUE eGrnBrokenPipe;
static VALUE eGrnDomainError;
static VALUE eGrnResultTooLarge;
static VALUE eGrnResourceDeadlockAvoided;
static VALUE eGrnNoMemoryAvailable;
static VALUE eGrnFilenameTooLong;
static VALUE eGrnNoLocksAvailable;
static VALUE eGrnFunctionNotImplemented;
static VALUE eGrnDirectoryNotEmpty;
static VALUE eGrnIllegalByteSequence;
static VALUE eGrnSocketNotInitialized;
static VALUE eGrnOperationWouldBlock;
static VALUE eGrnAddressIsNotAvailable;
static VALUE eGrnNetworkIsDown;
static VALUE eGrnNoBuffer;
static VALUE eGrnSocketIsAlreadyConnected;
static VALUE eGrnSocketIsNotConnected;
static VALUE eGrnSocketIsAlreadyShutdowned;
static VALUE eGrnOperationTimeout;
static VALUE eGrnConnectionRefused;
static VALUE eGrnRangeError;
static VALUE eGrnTokenizerError;
static VALUE eGrnFileCorrupt;
static VALUE eGrnInvalidFormat;
static VALUE eGrnObjectCorrupt;
static VALUE eGrnTooManySymbolicLinks;
static VALUE eGrnNotSocket;
static VALUE eGrnOperationNotSupported;
static VALUE eGrnAddressIsInUse;
static VALUE eGrnZLibError;
static VALUE eGrnLZOError;

VALUE
rb_grn_rc_to_exception (grn_rc rc)
{
    VALUE exception = Qnil;

    switch (rc) {
      case GRN_SUCCESS:
        break;
      case GRN_END_OF_DATA:
        exception = eGrnEndOfData;
        break;
      case GRN_UNKNOWN_ERROR:
        exception = eGrnUnknownError;
        break;
      case GRN_OPERATION_NOT_PERMITTED:
        exception = eGrnOperationNotPermitted;
        break;
      case GRN_NO_SUCH_FILE_OR_DIRECTORY:
        exception = eGrnNoSuchFileOrDirectory;
        break;
      case GRN_NO_SUCH_PROCESS:
        exception = eGrnNoSuchProcess;
        break;
      case GRN_INTERRUPTED_FUNCTION_CALL:
        exception = eGrnInterruptedFunctionCall;
        break;
      case GRN_INPUT_OUTPUT_ERROR:
        exception = eGrnInputOutputError;
        break;
      case GRN_NO_SUCH_DEVICE_OR_ADDRESS:
        exception = eGrnNoSuchDeviceOrAddress;
        break;
      case GRN_ARG_LIST_TOO_LONG:
        exception = eGrnArgListTooLong;
        break;
      case GRN_EXEC_FORMAT_ERROR:
        exception = eGrnExecFormatError;
        break;
      case GRN_BAD_FILE_DESCRIPTOR:
        exception = eGrnBadFileDescriptor;
        break;
      case GRN_NO_CHILD_PROCESSES:
        exception = eGrnNoChildProcesses;
        break;
      case GRN_RESOURCE_TEMPORARILY_UNAVAILABLE:
        exception = eGrnResourceTemporarilyUnavailable;
        break;
      case GRN_NOT_ENOUGH_SPACE:
        exception = eGrnNotEnoughSpace;
        break;
      case GRN_PERMISSION_DENIED:
        exception = eGrnPermissionDenied;
        break;
      case GRN_BAD_ADDRESS:
        exception = eGrnBadAddress;
        break;
      case GRN_RESOURCE_BUSY:
        exception = eGrnResourceBusy;
        break;
      case GRN_FILE_EXISTS:
        exception = eGrnFileExists;
        break;
      case GRN_IMPROPER_LINK:
        exception = eGrnImproperLink;
        break;
      case GRN_NO_SUCH_DEVICE:
        exception = eGrnNoSuchDevice;
        break;
      case GRN_NOT_A_DIRECTORY:
        exception = eGrnNotADirectory;
        break;
      case GRN_IS_A_DIRECTORY:
        exception = eGrnIsADirectory;
        break;
      case GRN_INVALID_ARGUMENT:
        exception = eGrnInvalidArgument;
        break;
      case GRN_TOO_MANY_OPEN_FILES_IN_SYSTEM:
        exception = eGrnTooManyOpenFilesInSystem;
        break;
      case GRN_TOO_MANY_OPEN_FILES:
        exception = eGrnTooManyOpenFiles;
        break;
      case GRN_INAPPROPRIATE_I_O_CONTROL_OPERATION:
        exception = eGrnInappropriateIOControlOperation;
        break;
      case GRN_FILE_TOO_LARGE:
        exception = eGrnFileTooLarge;
        break;
      case GRN_NO_SPACE_LEFT_ON_DEVICE:
        exception = eGrnNoSpaceLeftOnDevice;
        break;
      case GRN_INVALID_SEEK:
        exception = eGrnInvalidSeek;
        break;
      case GRN_READ_ONLY_FILE_SYSTEM:
        exception = eGrnReadOnlyFileSystem;
        break;
      case GRN_TOO_MANY_LINKS:
        exception = eGrnTooManyLinks;
        break;
      case GRN_BROKEN_PIPE:
        exception = eGrnBrokenPipe;
        break;
      case GRN_DOMAIN_ERROR:
        exception = eGrnDomainError;
        break;
      case GRN_RESULT_TOO_LARGE:
        exception = eGrnResultTooLarge;
        break;
      case GRN_RESOURCE_DEADLOCK_AVOIDED:
        exception = eGrnResourceDeadlockAvoided;
        break;
      case GRN_NO_MEMORY_AVAILABLE:
        exception = eGrnNoMemoryAvailable;
        break;
      case GRN_FILENAME_TOO_LONG:
        exception = eGrnFilenameTooLong;
        break;
      case GRN_NO_LOCKS_AVAILABLE:
        exception = eGrnNoLocksAvailable;
        break;
      case GRN_FUNCTION_NOT_IMPLEMENTED:
        exception = eGrnFunctionNotImplemented;
        break;
      case GRN_DIRECTORY_NOT_EMPTY:
        exception = eGrnDirectoryNotEmpty;
        break;
      case GRN_ILLEGAL_BYTE_SEQUENCE:
        exception = eGrnIllegalByteSequence;
        break;
      case GRN_SOCKET_NOT_INITIALIZED:
        exception = eGrnSocketNotInitialized;
        break;
      case GRN_OPERATION_WOULD_BLOCK:
        exception = eGrnOperationWouldBlock;
        break;
      case GRN_ADDRESS_IS_NOT_AVAILABLE:
        exception = eGrnAddressIsNotAvailable;
        break;
      case GRN_NETWORK_IS_DOWN:
        exception = eGrnNetworkIsDown;
        break;
      case GRN_NO_BUFFER:
        exception = eGrnNoBuffer;
        break;
      case GRN_SOCKET_IS_ALREADY_CONNECTED:
        exception = eGrnSocketIsAlreadyConnected;
        break;
      case GRN_SOCKET_IS_NOT_CONNECTED:
        exception = eGrnSocketIsNotConnected;
        break;
      case GRN_SOCKET_IS_ALREADY_SHUTDOWNED:
        exception = eGrnSocketIsAlreadyShutdowned;
        break;
      case GRN_OPERATION_TIMEOUT:
        exception = eGrnOperationTimeout;
        break;
      case GRN_CONNECTION_REFUSED:
        exception = eGrnConnectionRefused;
        break;
      case GRN_RANGE_ERROR:
        exception = eGrnRangeError;
        break;
      case GRN_TOKENIZER_ERROR:
        exception = eGrnTokenizerError;
        break;
      case GRN_FILE_CORRUPT:
        exception = eGrnFileCorrupt;
        break;
      case GRN_INVALID_FORMAT:
        exception = eGrnInvalidFormat;
        break;
      case GRN_OBJECT_CORRUPT:
        exception = eGrnObjectCorrupt;
        break;
      case GRN_TOO_MANY_SYMBOLIC_LINKS:
        exception = eGrnTooManySymbolicLinks;
        break;
      case GRN_NOT_SOCKET:
        exception = eGrnNotSocket;
        break;
      case GRN_OPERATION_NOT_SUPPORTED:
        exception = eGrnOperationNotSupported;
        break;
      case GRN_ADDRESS_IS_IN_USE:
        exception = eGrnAddressIsInUse;
        break;
      case GRN_ZLIB_ERROR:
        exception = eGrnZLibError;
        break;
      case GRN_LZO_ERROR:
        exception = eGrnLZOError;
        break;
      default:
        rb_raise(rb_eGrnError, "invalid return code: %d", rc);
        break;
    }

    return exception;
}

const char *
rb_grn_rc_to_message (grn_rc rc)
{
    const char *message = NULL;

    switch (rc) {
      case GRN_SUCCESS:
	break;
      case GRN_END_OF_DATA:
        message = "end of data";
        break;
      case GRN_UNKNOWN_ERROR:
        message = "unknown error";
        break;
      case GRN_OPERATION_NOT_PERMITTED:
        message = "operation not permitted";
        break;
      case GRN_NO_SUCH_FILE_OR_DIRECTORY:
        message = "no such file or directory";
        break;
      case GRN_NO_SUCH_PROCESS:
        message = "no such process";
        break;
      case GRN_INTERRUPTED_FUNCTION_CALL:
        message = "interrupted function call";
        break;
      case GRN_INPUT_OUTPUT_ERROR:
        message = "input output error";
        break;
      case GRN_NO_SUCH_DEVICE_OR_ADDRESS:
        message = "no such device or address";
        break;
      case GRN_ARG_LIST_TOO_LONG:
        message = "arg list too long";
        break;
      case GRN_EXEC_FORMAT_ERROR:
        message = "exec format error";
        break;
      case GRN_BAD_FILE_DESCRIPTOR:
        message = "bad file descriptor";
        break;
      case GRN_NO_CHILD_PROCESSES:
        message = "no child processes";
        break;
      case GRN_RESOURCE_TEMPORARILY_UNAVAILABLE:
        message = "resource temporarily unavailable";
        break;
      case GRN_NOT_ENOUGH_SPACE:
        message = "not enough space";
        break;
      case GRN_PERMISSION_DENIED:
        message = "permission denied";
        break;
      case GRN_BAD_ADDRESS:
        message = "bad address";
        break;
      case GRN_RESOURCE_BUSY:
        message = "resource busy";
        break;
      case GRN_FILE_EXISTS:
        message = "file exists";
        break;
      case GRN_IMPROPER_LINK:
        message = "improper link";
        break;
      case GRN_NO_SUCH_DEVICE:
        message = "no such device";
        break;
      case GRN_NOT_A_DIRECTORY:
        message = "not a directory";
        break;
      case GRN_IS_A_DIRECTORY:
        message = "is a directory";
        break;
      case GRN_INVALID_ARGUMENT:
        message = "invalid argument";
        break;
      case GRN_TOO_MANY_OPEN_FILES_IN_SYSTEM:
        message = "too many open files in system";
        break;
      case GRN_TOO_MANY_OPEN_FILES:
        message = "too many open files";
        break;
      case GRN_INAPPROPRIATE_I_O_CONTROL_OPERATION:
        message = "inappropriate i o control operation";
        break;
      case GRN_FILE_TOO_LARGE:
        message = "file too large";
        break;
      case GRN_NO_SPACE_LEFT_ON_DEVICE:
        message = "no space left on device";
        break;
      case GRN_INVALID_SEEK:
        message = "invalid seek";
        break;
      case GRN_READ_ONLY_FILE_SYSTEM:
        message = "read only file system";
        break;
      case GRN_TOO_MANY_LINKS:
        message = "too many links";
        break;
      case GRN_BROKEN_PIPE:
        message = "broken pipe";
        break;
      case GRN_DOMAIN_ERROR:
        message = "domain error";
        break;
      case GRN_RESULT_TOO_LARGE:
        message = "result too large";
        break;
      case GRN_RESOURCE_DEADLOCK_AVOIDED:
        message = "resource deadlock avoided";
        break;
      case GRN_NO_MEMORY_AVAILABLE:
        message = "no memory available";
        break;
      case GRN_FILENAME_TOO_LONG:
        message = "filename too long";
        break;
      case GRN_NO_LOCKS_AVAILABLE:
        message = "no locks available";
        break;
      case GRN_FUNCTION_NOT_IMPLEMENTED:
        message = "function not implemented";
        break;
      case GRN_DIRECTORY_NOT_EMPTY:
        message = "directory not empty";
        break;
      case GRN_ILLEGAL_BYTE_SEQUENCE:
        message = "illegal byte sequence";
        break;
      case GRN_SOCKET_NOT_INITIALIZED:
        message = "socket not initialized";
        break;
      case GRN_OPERATION_WOULD_BLOCK:
        message = "operation would block";
        break;
      case GRN_ADDRESS_IS_NOT_AVAILABLE:
        message = "address is not available";
        break;
      case GRN_NETWORK_IS_DOWN:
        message = "network is down";
        break;
      case GRN_NO_BUFFER:
        message = "no buffer";
        break;
      case GRN_SOCKET_IS_ALREADY_CONNECTED:
        message = "socket is already connected";
        break;
      case GRN_SOCKET_IS_NOT_CONNECTED:
        message = "socket is not connected";
        break;
      case GRN_SOCKET_IS_ALREADY_SHUTDOWNED:
        message = "socket is already shutdowned";
        break;
      case GRN_OPERATION_TIMEOUT:
        message = "operation timeout";
        break;
      case GRN_CONNECTION_REFUSED:
        message = "connection refused";
        break;
      case GRN_RANGE_ERROR:
        message = "range error";
        break;
      case GRN_TOKENIZER_ERROR:
        message = "tokenizer error";
        break;
      case GRN_FILE_CORRUPT:
        message = "file corrupt";
        break;
      case GRN_INVALID_FORMAT:
        message = "invalid format";
        break;
      case GRN_OBJECT_CORRUPT:
        message = "object corrupt";
        break;
      case GRN_TOO_MANY_SYMBOLIC_LINKS:
        message = "too many symbolic links";
        break;
      case GRN_NOT_SOCKET:
        message = "not socket";
        break;
      case GRN_OPERATION_NOT_SUPPORTED:
        message = "operation not supported";
        break;
      case GRN_ADDRESS_IS_IN_USE:
        message = "address is in use";
        break;
      case GRN_ZLIB_ERROR:
        message = "ZLib error";
        break;
      case GRN_LZO_ERROR:
        message = "LZO error";
        break;
      default:
        rb_raise(rb_eGrnError, "invalid return code: %d", rc);
        break;
    }

    return message;
}

void
rb_grn_check_rc (grn_rc rc)
{
    VALUE exception;
    const char *message;

    exception = rb_grn_rc_to_exception(rc);
    if (NIL_P(exception))
	return;
    message = rb_grn_rc_to_message(rc);

    rb_raise(exception, "%s", message);
}

void
rb_grn_init_exception (VALUE mGroonga)
{
    rb_eGrnError =
        rb_define_class_under(mGroonga, "Error", rb_eStandardError);
    eGrnEndOfData =
        rb_define_class_under(mGroonga, "EndOfData", rb_eGrnError);
    eGrnUnknownError =
        rb_define_class_under(mGroonga, "UnknownError", rb_eGrnError);
    eGrnOperationNotPermitted =
        rb_define_class_under(mGroonga, "OperationNotPermitted", rb_eGrnError);
    eGrnNoSuchFileOrDirectory =
        rb_define_class_under(mGroonga, "NoSuchFileOrDirectory", rb_eGrnError);
    eGrnNoSuchProcess =
        rb_define_class_under(mGroonga, "NoSuchProcess", rb_eGrnError);
    eGrnInterruptedFunctionCall =
        rb_define_class_under(mGroonga, "InterruptedFunctionCall", rb_eGrnError);
    eGrnInputOutputError =
        rb_define_class_under(mGroonga, "InputOutputError", rb_eGrnError);
    eGrnNoSuchDeviceOrAddress =
        rb_define_class_under(mGroonga, "NoSuchDeviceOrAddress", rb_eGrnError);
    eGrnArgListTooLong =
        rb_define_class_under(mGroonga, "ArgListTooLong", rb_eGrnError);
    eGrnExecFormatError =
        rb_define_class_under(mGroonga, "ExecFormatError", rb_eGrnError);
    eGrnBadFileDescriptor =
        rb_define_class_under(mGroonga, "BadFileDescriptor", rb_eGrnError);
    eGrnNoChildProcesses =
        rb_define_class_under(mGroonga, "NoChildProcesses", rb_eGrnError);
    eGrnResourceTemporarilyUnavailable =
        rb_define_class_under(mGroonga, "ResourceTemporarilyUnavailable", rb_eGrnError);
    eGrnNotEnoughSpace =
        rb_define_class_under(mGroonga, "NotEnoughSpace", rb_eGrnError);
    eGrnPermissionDenied =
        rb_define_class_under(mGroonga, "PermissionDenied", rb_eGrnError);
    eGrnBadAddress =
        rb_define_class_under(mGroonga, "BadAddress", rb_eGrnError);
    eGrnResourceBusy =
        rb_define_class_under(mGroonga, "ResourceBusy", rb_eGrnError);
    eGrnFileExists =
        rb_define_class_under(mGroonga, "FileExists", rb_eGrnError);
    eGrnImproperLink =
        rb_define_class_under(mGroonga, "ImproperLink", rb_eGrnError);
    eGrnNoSuchDevice =
        rb_define_class_under(mGroonga, "NoSuchDevice", rb_eGrnError);
    eGrnNotADirectory =
        rb_define_class_under(mGroonga, "NotADirectory", rb_eGrnError);
    eGrnIsADirectory =
        rb_define_class_under(mGroonga, "IsADirectory", rb_eGrnError);
    eGrnInvalidArgument =
        rb_define_class_under(mGroonga, "InvalidArgument", rb_eGrnError);
    eGrnTooManyOpenFilesInSystem =
        rb_define_class_under(mGroonga, "TooManyOpenFilesInSystem", rb_eGrnError);
    eGrnTooManyOpenFiles =
        rb_define_class_under(mGroonga, "TooManyOpenFiles", rb_eGrnError);
    eGrnInappropriateIOControlOperation =
        rb_define_class_under(mGroonga, "InappropriateIOControlOperation", rb_eGrnError);
    eGrnFileTooLarge =
        rb_define_class_under(mGroonga, "FileTooLarge", rb_eGrnError);
    eGrnNoSpaceLeftOnDevice =
        rb_define_class_under(mGroonga, "NoSpaceLeftOnDevice", rb_eGrnError);
    eGrnInvalidSeek =
        rb_define_class_under(mGroonga, "InvalidSeek", rb_eGrnError);
    eGrnReadOnlyFileSystem =
        rb_define_class_under(mGroonga, "ReadOnlyFileSystem", rb_eGrnError);
    eGrnTooManyLinks =
        rb_define_class_under(mGroonga, "TooManyLinks", rb_eGrnError);
    eGrnBrokenPipe =
        rb_define_class_under(mGroonga, "BrokenPipe", rb_eGrnError);
    eGrnDomainError =
        rb_define_class_under(mGroonga, "DomainError", rb_eGrnError);
    eGrnResultTooLarge =
        rb_define_class_under(mGroonga, "ResultTooLarge", rb_eGrnError);
    eGrnResourceDeadlockAvoided =
        rb_define_class_under(mGroonga, "ResourceDeadlockAvoided", rb_eGrnError);
    eGrnNoMemoryAvailable =
        rb_define_class_under(mGroonga, "NoMemoryAvailable", rb_eGrnError);
    eGrnFilenameTooLong =
        rb_define_class_under(mGroonga, "FilenameTooLong", rb_eGrnError);
    eGrnNoLocksAvailable =
        rb_define_class_under(mGroonga, "NoLocksAvailable", rb_eGrnError);
    eGrnFunctionNotImplemented =
        rb_define_class_under(mGroonga, "FunctionNotImplemented", rb_eGrnError);
    eGrnDirectoryNotEmpty =
        rb_define_class_under(mGroonga, "DirectoryNotEmpty", rb_eGrnError);
    eGrnIllegalByteSequence =
        rb_define_class_under(mGroonga, "IllegalByteSequence", rb_eGrnError);
    eGrnSocketNotInitialized =
        rb_define_class_under(mGroonga, "SocketNotInitialized", rb_eGrnError);
    eGrnOperationWouldBlock =
        rb_define_class_under(mGroonga, "OperationWouldBlock", rb_eGrnError);
    eGrnAddressIsNotAvailable =
        rb_define_class_under(mGroonga, "AddressIsNotAvailable", rb_eGrnError);
    eGrnNetworkIsDown =
        rb_define_class_under(mGroonga, "NetworkIsDown", rb_eGrnError);
    eGrnNoBuffer =
        rb_define_class_under(mGroonga, "NoBuffer", rb_eGrnError);
    eGrnSocketIsAlreadyConnected =
        rb_define_class_under(mGroonga, "SocketIsAlreadyConnected", rb_eGrnError);
    eGrnSocketIsNotConnected =
        rb_define_class_under(mGroonga, "SocketIsNotConnected", rb_eGrnError);
    eGrnSocketIsAlreadyShutdowned =
        rb_define_class_under(mGroonga, "SocketIsAlreadyShutdowned", rb_eGrnError);
    eGrnOperationTimeout =
        rb_define_class_under(mGroonga, "OperationTimeout", rb_eGrnError);
    eGrnConnectionRefused =
        rb_define_class_under(mGroonga, "ConnectionRefused", rb_eGrnError);
    eGrnRangeError =
        rb_define_class_under(mGroonga, "RangeError", rb_eGrnError);
    eGrnTokenizerError =
        rb_define_class_under(mGroonga, "TokenizerError", rb_eGrnError);
    eGrnFileCorrupt =
        rb_define_class_under(mGroonga, "FileCorrupt", rb_eGrnError);
    eGrnInvalidFormat =
        rb_define_class_under(mGroonga, "InvalidFormat", rb_eGrnError);
    eGrnObjectCorrupt =
        rb_define_class_under(mGroonga, "ObjectCorrupt", rb_eGrnError);
    eGrnTooManySymbolicLinks =
        rb_define_class_under(mGroonga, "TooManySymbolicLinks", rb_eGrnError);
    eGrnNotSocket =
        rb_define_class_under(mGroonga, "NotSocket", rb_eGrnError);
    eGrnOperationNotSupported =
        rb_define_class_under(mGroonga, "OperationNotSupported", rb_eGrnError);
    eGrnAddressIsInUse =
        rb_define_class_under(mGroonga, "AddressIsInUse", rb_eGrnError);
    eGrnZLibError =
        rb_define_class_under(mGroonga, "ZLibError", rb_eGrnError);
    eGrnLZOError =
        rb_define_class_under(mGroonga, "LZOError", rb_eGrnError);
}

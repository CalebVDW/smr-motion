/**
 * \ingroup SmrCommon
 * \file logger.h
 *	mainly defines the Logger class
 */

#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <log4cplus/logger.h>
#include <log4cplus/configurator.h>
#include <log4cplus/loggingmacros.h>
#include <iomanip>

using namespace log4cplus;

//This preprocessor branch encodes the string literal differntly if the code is being run from Unreal 
#ifdef UNREAL_SMR_BINDING
log4cplus::tstring name = L"main";
static Logger logger = Logger::getInstance(name);
#else
static Logger logger = Logger::getInstance("main");
#endif
static BasicConfigurator config;

#define    LOG_TRACE LOG4CPLUS_TRACE
#define    LOG_DEBUG LOG4CPLUS_DEBUG
#define    LOG_INFO LOG4CPLUS_INFO
#define    LOG_WARN LOG4CPLUS_WARN
#define    LOG_ERROR LOG4CPLUS_ERROR
#define    LOG_FATAL LOG4CPLUS_FATAL

#endif



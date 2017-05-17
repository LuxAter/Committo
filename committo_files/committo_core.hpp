#ifndef COMMITTO_CORE_HPP
#define COMMITTO_CORE_HPP
#include <curl/curl.h>
/*!The core namespace containing all members for the library.
 */
namespace committo {
  enum CommittoSetting { FOLLOWLOCATION };
  extern CURL* curl_handle;    /*!<Handle for curl/libcurl members.*/
  extern CURLcode curl_output; /*!<curl/libcurl output.*/
                               /*! Initializes Committo and Curl libraries.
                                * This function defines curl_handle, and must be called before any other
                                * committo method call.
                                */
  void InitCommitto();
  /*! Terminates Committo and Curl libraries.
   * This function cleans up everything done by committo and curl, and must be
   * called last.
   */
  void TermCommitto();
  void SetCommitto(int setting, int value);
}
#endif

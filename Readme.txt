WinHttpClient for HTTPS:

inline bool SendHttpRequest(const wstring &httpVerb = L"GET", bool disableAutoRedirect = false, bool securityConnection = false);

securityConnection = true;

If HTTPS server has self-signed certificate,  call SetRequireValidSslCertificates() with 'false', 
for a normal certificate it can be  'true' or 'false'.
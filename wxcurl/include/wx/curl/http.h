/*
*	http.h
*	wxCURL
*
*	Created by Casey O'Donnell on Tue Jun 29 2004.
*	Copyright (c) 2004 Casey O'Donnell. All rights reserved.
*
*	Licence: wxWidgets Licence
*/

#ifndef _WXCURLHTTP_H__INCLUDED_
#define _WXCURLHTTP_H__INCLUDED_

#include <wx/curl/base.h>

// C Function Declarations for LibCURL
//
//////////////////////////////////////////////////////////////////////

extern "C"
{
}

// http.h: interface for the wxCurlHTTP class.
//
//////////////////////////////////////////////////////////////////////

//! A specialized interface to HTTP derived from wxCurlBase.
class WXDLLIMPEXP_CURL wxCurlHTTP : public wxCurlBase
{
public:
    wxCurlHTTP(const wxString& szURL = wxEmptyString,
            const wxString& szUserName = wxEmptyString,
            const wxString& szPassword = wxEmptyString,
            wxEvtHandler* pEvtHandler = NULL, int id = wxID_ANY,
            long flags = wxCURL_DEFAULT_FLAGS);
    virtual ~wxCurlHTTP();
    void        AddHeader(const wxString& szHeaderString){m_arrHeaders.Add(szHeaderString);}
    // Post Data Methods
    bool        AddForm(const bool& bClear, const wxString& szName,
                        struct curl_forms* pForms, CURLFORMcode* outErr=NULL);
    bool        AddBufferToForm(const bool& bClear, const wxString& szName,
                                char* buffer, size_t len, CURLFORMcode* outErr=NULL);

    // Member Data Access Methods (MDA)

    // MDA - Get/Set Cookie Use
    void        UseCookies(const bool& bUseCookies);
    bool        UseCookies() const;

    // MDA - Get/Set Cookie File
    void        SetCookieFile(const wxString& szFilePath);
    wxString    GetCookieFile() const;

    //MDA Sets User-Agent.
    void		SetUserAgent(const wxString& szUserAgent);
    wxString	GetUserAgent() const;

    //MDA Sets Range for the Get request.
    void		SetRange(const wxLongLong& llRange) {m_llRange = llRange;}
    wxLongLong	GetRange() const {return m_llRange;}

    // MDA - Get/Set Certificate verification
    void        VerifyHostCert(const bool& bVerifyHostCert){m_bVerifyHostCert = bVerifyHostCert;}
    bool        IsVerifyHostCert() const { return m_bVerifyHostCert;}
    void        VerifyPeerCert(const bool& bVerifyPeerCert){m_bVerifyHostCert = bVerifyPeerCert;}
    bool        IsVerifyPeerCert() const { return m_bVerifyPeerCert;}
    void        VerifyProxyHostCert(const bool& bVerifyProxyHostCert){m_bVerifyHostCert = bVerifyProxyHostCert;}
    bool        IsVerifyProxyHostCert() const { return m_bVerifyProxyHostCert;}
    void        VerifyProxyPeerCert(const bool& bVerifyProxyPeerCert){m_bVerifyProxyPeerCert = bVerifyProxyPeerCert;}
    bool        IsVerifyProxyPeerCert() const { return m_bVerifyProxyPeerCert;}

    // Action Methods - These All Make Calls To: curl_easy_perform()

    // OPTIONS - This Method Allows a Caller to Query the Capabilities of a Resource
    bool        Options(const wxString& szRemoteFile = wxEmptyString);

    // HEAD - This Method is Similar to GET, Though no Message Body is Retrieved
    bool        Head(const wxString& szRemoteFile = wxEmptyString);

    // POST - These Methods Post Data Passed In
    bool        Post(const char* buffer, size_t size, const wxString& szRemoteFile = wxEmptyString);
    bool        Post(wxInputStream& buffer, const wxString& szRemoteFile = wxEmptyString);

    // POST - This Method Uses Data As Defined By AddForm(...)
    bool        Post(const wxString& szRemoteFile = wxEmptyString);

    // TRACE - This Method Allows a Caller to Perform Diagnostic Tests
    bool        Trace(const wxString& szRemoteFile = wxEmptyString);

    // GET - These Methods Allow a Caller to Retrieve a Given Resource
    bool        Get(const wxString& szFilePath, const wxString& szRemoteFile = wxEmptyString);
    size_t      Get(char*& buffer, const wxString& szRemoteFile = wxEmptyString);
    bool        Get(wxOutputStream& buffer, const wxString& szRemoteFile = wxEmptyString);

    // PUT - These Methods Allow a Caller to Place a Resource on the Host
    bool        Put(const wxString& szFilePath, const wxString& szRemoteFile = wxEmptyString);
    bool        Put(const char* buffer, size_t size, const wxString& szRemoteFile = wxEmptyString);
    bool        Put(wxInputStream& buffer, const wxString& szRemoteFile = wxEmptyString);

    // DELETE - This Method Allows a Caller to Remove a Resource
    bool        Delete(const wxString& szRemoteLoc = wxEmptyString);

protected:

    virtual void ResetPostData();
    virtual void SetCurlHandleToDefaults(const wxString& relativeURL);

    bool IsResponseOk() const;


    struct curl_httppost*   m_pPostHead;
    struct curl_httppost*   m_pPostTail;

    bool                    m_bUseCookies;

    wxCharBuffer            m_szCookieFile;

    const char*             m_pszPostFieldsData;
    size_t                  m_iPostDataSize;

	// Aditional options

	wxCharBuffer            m_szUserAgent;
	wxLongLong              m_llRange;

	// for SSL

	bool                    m_bVerifyHostCert;
	bool                    m_bVerifyPeerCert;
	bool                    m_bVerifyProxyHostCert;
	bool                    m_bVerifyProxyPeerCert;
};

#endif // _WXCURLHTTP_H__INCLUDED_

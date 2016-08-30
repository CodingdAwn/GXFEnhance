// Connect.cpp : CConnect �ľ���ʵ��
#include "stdafx.h"
#include "AddIn.h"
#include "Connect.h"

extern CAddInModule _AtlModule;

// CConnect
STDMETHODIMP CConnect::OnConnection(IDispatch *pApplication, ext_ConnectMode ConnectMode, IDispatch *pAddInInst, SAFEARRAY ** /*�Զ���*/ )
{
	HRESULT hr = S_OK;
	pApplication->QueryInterface(__uuidof(DTE2), (LPVOID*)&m_pDTE);
	pAddInInst->QueryInterface(__uuidof(AddIn), (LPVOID*)&m_pAddInInstance);
// 	if(ConnectMode == 5) //5 == ext_cm_UISetup
	{
		HRESULT hr = S_OK;
		CComPtr<IDispatch> pDisp;
		CComQIPtr<Commands> pCommands;
		CComQIPtr<Commands2> pCommands2;
		CComQIPtr<_CommandBars> pCommandBars;
		CComPtr<CommandBarControl> pCommandBarControl;
		CComPtr<Command> pCreatedCommand;
		CComPtr<CommandBar> pMenuBarCommandBar;
		CComPtr<CommandBarControls> pMenuBarControls;
		CComPtr<CommandBarControl> pToolsCommandBarControl;
		CComQIPtr<CommandBar> pToolsCommandBar;
		CComQIPtr<CommandBarPopup> pToolsPopup;

		IfFailGoCheck(m_pDTE->get_Commands(&pCommands), pCommands);
		pCommands2 = pCommands;
		long lCount = 0;
		HRESULT hRet = pCommands2->get_Count(&lCount);
		for (long i = lCount; i > 0; --i)
		{
			CComPtr<Command> pCommandTest;
			pCommands2->Item(CComVariant(i), -1, &pCommandTest);
			if (pCommandTest)
			{
				BSTR str;
				pCommandTest->get_Name(&str);
				_bstr_t bStr = str;
				char* pStr = bStr;
				if ( strstr(pStr, "GXFEnhance") != NULL )
				{
					pCommandTest->Delete();
				}
			}
		}

		hRet = pCommands2->get_Count(&lCount);
		for (long j = lCount; j > 0; --j)
		{
			CComPtr<Command> pCommandTest;
			pCommands2->Item(CComVariant(j), -1, &pCommandTest);
			if (pCommandTest)
			{
				BSTR str;
				pCommandTest->get_Name(&str);
				_bstr_t bStr = str;
				char* pStr = bStr;
				if ( strstr(pStr, "GXFEnhance") != NULL )
				{
					pCommandTest->Delete();
				}
			}
		}

// 		CComPtr<Command> pCommandTest;
// 		HRESULT hRet = pCommands2->Item(CComVariant(L"GXFEnhance"), -1, &pCommandTest);
// 		if (S_OK != hRet || pCommandTest == NULL)
// 		{
// 			goto Error;
// 		}

		HRESULT hRet2 = pCommands2->AddNamedCommand2(m_pAddInInstance, CComBSTR("GXFEnhance"), CComBSTR("GXFEnhance"), CComBSTR("GXFEnhance"),
			VARIANT_TRUE, CComVariant(101), NULL, vsCommandStatusSupported+vsCommandStatusEnabled, vsCommandStylePictAndText, vsCommandControlTypeButton, &pCreatedCommand);
		if( S_OK == hRet2 && pCreatedCommand )
		{
			//�ڡ����ߡ��˵��������һ����ť��
			IfFailGoCheck(m_pDTE->get_CommandBars(&pDisp), pDisp);
			pCommandBars = pDisp;

			//���� MenuBar �����������������������������˵���Ķ���������:
			IfFailGoCheck(pCommandBars->get_Item(CComVariant(L"MenuBar"), &pMenuBarCommandBar), pMenuBarCommandBar);
			IfFailGoCheck(pMenuBarCommandBar->get_Controls(&pMenuBarControls), pMenuBarControls);

			int lCount = 0;
			pMenuBarControls->get_Count(&lCount);
			for(long i = 0; i < lCount; ++i)
			{
				CComPtr<CommandBarControl> pTest;
				pMenuBarControls->get_Item(CComVariant(i), &pTest);
				if (pTest)
				{
					BSTR str;
					pTest->get_Caption(&str);
					int n = 0;
				}
			}

			//�� MenuBar �������ϲ��ҡ����ߡ�������:
			IfFailGoCheck(pMenuBarControls->get_Item(CComVariant(L"����"), &pToolsCommandBarControl), pToolsCommandBarControl);
			pToolsPopup = pToolsCommandBarControl;
			IfFailGoCheck(pToolsPopup->get_CommandBar(&pToolsCommandBar), pToolsCommandBar);

			//��ӿؼ�:
			pDisp = NULL;
			IfFailGoCheck(pCreatedCommand->AddControl(pToolsCommandBar, 1, &pDisp), pDisp);
		}
		return S_OK;
	}
Error:
	return hr;
}

STDMETHODIMP CConnect::OnDisconnection(ext_DisconnectMode /*RemoveMode*/, SAFEARRAY ** /*�Զ���*/ )
{
	m_pDTE = NULL;
	m_pAddInInstance = NULL;
	return S_OK;
}

STDMETHODIMP CConnect::OnAddInsUpdate (SAFEARRAY ** /*�Զ���*/ )
{
	return S_OK;
}

STDMETHODIMP CConnect::OnStartupComplete (SAFEARRAY ** /*�Զ���*/ )
{
	return S_OK;
}

STDMETHODIMP CConnect::OnBeginShutdown (SAFEARRAY ** /*�Զ���*/ )
{
	return S_OK;
}

STDMETHODIMP CConnect::QueryStatus(BSTR bstrCmdName, vsCommandStatusTextWanted NeededText, vsCommandStatus *pStatusOption, VARIANT *pvarCommandText)
{
  if(NeededText == vsCommandStatusTextWantedNone)
	{
	  if(!_wcsicmp(bstrCmdName, L"GXFEnhance.Connect.GXFEnhance"))
	  {
		  *pStatusOption = (vsCommandStatus)(vsCommandStatusEnabled+vsCommandStatusSupported);
	  }
  }
	return S_OK;
}

STDMETHODIMP CConnect::Exec(BSTR bstrCmdName, vsCommandExecOption ExecuteOption, VARIANT * /*pvarVariantIn*/, VARIANT * /*pvarVariantOut*/, VARIANT_BOOL *pvbHandled)
{
	*pvbHandled = VARIANT_FALSE;
	if(ExecuteOption == vsCommandExecOptionDoDefault)
	{
		if(!_wcsicmp(bstrCmdName, L"GXFEnhance.Connect.GXFEnhance"))
		{
			*pvbHandled = VARIANT_TRUE;
			return S_OK;
		}
	}
	return S_OK;
}
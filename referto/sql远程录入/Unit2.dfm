object DataModule2: TDataModule2
  OldCreateOrder = False
  Height = 383
  Width = 309
  object ADOConnection1: TADOConnection
    ConnectionString = 
      'Provider=SQLOLEDB.1;Password=zhls863179;Persist Security Info=Tr' +
      'ue;User ID=sa;Initial Catalog=lsmaster;Data Source=61.143.235.23' +
      '7;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=40' +
      '96;Workstation ID=PCOS-20131030LK;Use Encryption for Data=False;' +
      'Tag with column collation when possible=False'
    LoginPrompt = False
    Provider = 'SQLOLEDB.1'
    Left = 216
    Top = 24
  end
  object FDQman: TADOQuery
    Connection = ADOConnection1
    CursorType = ctStatic
    Parameters = <>
    SQL.Strings = (
      'select top 50  *  from man')
    Left = 232
    Top = 112
  end
  object FDQveh: TADOQuery
    Connection = ADOConnection1
    CursorType = ctStatic
    Parameters = <>
    SQL.Strings = (
      'select top 10 *  from vehicle')
    Left = 216
    Top = 184
  end
  object FDQfindveh: TADOQuery
    Connection = ADOConnection1
    CursorType = ctStatic
    Parameters = <>
    SQL.Strings = (
      'select top 10  *  from vehicle')
    Left = 160
    Top = 208
  end
  object FDQsaveman: TADOQuery
    Connection = ADOConnection1
    CursorType = ctStatic
    Parameters = <>
    SQL.Strings = (
      'select top 5 *  from man')
    Left = 88
    Top = 256
  end
  object ADOQcust: TADOQuery
    Connection = ADOConnection1
    CursorType = ctStatic
    Parameters = <>
    SQL.Strings = (
      'select  *  from customer')
    Left = 144
    Top = 72
  end
end

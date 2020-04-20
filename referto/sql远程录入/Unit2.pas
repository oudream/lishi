unit Unit2;

interface

uses
  System.SysUtils, System.Classes, FireDAC.Stan.Intf, FireDAC.Stan.Option,
  FireDAC.Stan.Error, FireDAC.UI.Intf, FireDAC.Phys.Intf, FireDAC.Stan.Def,
  FireDAC.Stan.Pool, FireDAC.Stan.Async, FireDAC.Phys, Data.DB,
  FireDAC.Comp.Client, FireDAC.Phys.ODBCBase, FireDAC.Phys.MSSQL,
  FireDAC.Stan.Param, FireDAC.DatS, FireDAC.DApt.Intf, FireDAC.DApt,
  FireDAC.Comp.DataSet, FireDAC.FMXUI.Wait, FireDAC.Comp.UI, Data.Win.ADODB;

type
  TDataModule2 = class(TDataModule)
    ADOConnection1: TADOConnection;
    FDQman: TADOQuery;
    FDQveh: TADOQuery;
    FDQfindveh: TADOQuery;
    FDQsaveman: TADOQuery;
    ADOQcust: TADOQuery;
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  DataModule2: TDataModule2;

implementation

{%CLASSGROUP 'FMX.Controls.TControl'}

{$R *.dfm}

end.

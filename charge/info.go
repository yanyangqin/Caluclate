package charge

import (
	"SysAdmin_Server/handler"
	sysLog "SysAdmin_Server/handler/sys-trading/logging"
	sysSetting "SysAdmin_Server/model/sys-setting"
	"SysAdmin_Server/pkg/errno"
	"SysAdmin_Server/pkg/global"
	"encoding/json"

	"github.com/gin-gonic/gin"
)

type ReqCharge struct {
	Page int64 `json:"page"`
	Size int64 `json:"size"`

	ProductType      int64  `json:"productType"`
	ChargeSchemeCode string `json:"chargeSchemeCode"`
	Underlyer        string `json:"underlyer"`
	Exchange         string `json:"exchange"`
	ChargeCurrency   string `json:"chargeCurrency"`
	ClientClass      string `json:"clientClass"`
}

func ChargeInfo(ctx *gin.Context) {
	log := sysLog.ALog{
		ActionID: "ChargeInfo",
	}
	var req ReqCharge

	if err := ctx.ShouldBindJSON(&req); err != nil {
		handler.SendResponseWithLog(ctx, log, errno.New(errno.ErrBind, err), nil)
		return
	}

	reqJson, _ := json.Marshal(&req)
	log.ActionDetail = string(reqJson)

	result := struct {
		Total int32               `json:"total"`
		List  []sysSetting.Charge `json:"list"`
	}{}

	err := sysSetting.GetCharge(global.GTradingDb, req.Page, req.Size, req.ProductType, req.ChargeSchemeCode, req.Underlyer, req.Exchange, req.ChargeCurrency, req.ClientClass, &result.Total, &result.List)
	if err != nil {
		handler.SendResponseWithLog(ctx, log, errno.New(errno.ErrDatabase, err), nil)
		return
	}

	handler.SendResponseWithLog(ctx, log, nil, result)
}

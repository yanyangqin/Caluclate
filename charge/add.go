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

type ReqAddCharge struct {
	Charge []sysSetting.Charge
}

func AddChargeInfo(ctx *gin.Context) {
	log := sysLog.ALog{
		ActionID: "AddCharge",
	}
	var req ReqAddCharge

	if err := ctx.ShouldBindJSON(&req.Charge); err != nil {
		handler.SendResponseWithLog(ctx, log, errno.New(errno.ErrBind, err), nil)
		return
	}

	reqJson, _ := json.Marshal(&req.Charge)
	log.ActionDetail = string(reqJson)

	tx := global.GTradingDb.Begin()
	for _, cal := range req.Charge {
		if cal.ChargeSchemeCode == "" {
			tx.Rollback()
			handler.SendResponseWithLog(ctx, log, errno.New(errno.ErrChargeSchemeCode, nil), nil)
			return
		}

		err := cal.Create(tx)
		if err != nil {
			tx.Rollback()
			handler.SendResponseWithLog(ctx, log, errno.New(errno.ErrDatabase, err), nil)
			return
		}
		tx.Commit()
	}

	handler.SendResponseWithLog(ctx, log, nil, nil)
}

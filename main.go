package main

import (
	"net/http"

	"github.com/gin-gonic/gin"
)

var output = "S"

func main() {
	router := gin.New()
	router.GET("/", func(c *gin.Context) {
		c.JSON(http.StatusOK,
			gin.H{"output": output},
		)
	})
	router.PATCH("/change/:name", func(c *gin.Context) {
		name := c.Param("name")
		output = name
		c.JSON(http.StatusOK,
			gin.H{"output": output},
		)
	})

	router.Run(":3000")
}

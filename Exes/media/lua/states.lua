State_Prueba = {}

State_Prueba["Enter"] = function(agent)

	print ("[Lua]: Enter")

end

State_Prueba["Execute"] = function(agent)

	--agent: SayHello()
	print ("--> PROBANDO FUNCIONES CON ARGUMENTOS")

end

State_Prueba["Exit"] = function(agent)

	print ("[Lua]: Exit")

end

State_Prueba["Probando"] = function()
	
	print ("--> PROBANDO FUNCIONES SIN ARGUMENTOS")

end

State_Prueba["ProbandoConArgumentos"] = function(agent)

	print ("--> PROBANDO FUNCIONES CON ARGUMENTOS")

end
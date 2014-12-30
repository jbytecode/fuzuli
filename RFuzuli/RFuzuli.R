Identity <- function(x){
    return(x)
}

# Class FuzuliSource
FuzuliSource <- setRefClass("FuzuliSource",
	fields = list(
				 fileName="character",
			     sourceCode="character",
				 isDebug="logical"),
	methods = list (
		# Constructor
		initialize = function(){
			isDebug <<- FALSE
		},
        

		# Debugging output
		DEBUG = function(...){
			if(isDebug){
				cat(...)
				cat("\n")
			}
		},

        # Setting source from string
        readString = function(txt){
          .self$sourceCode <- txt  
        },
        
		# Reading source file
		readFile = function(filename){
            .self$fileName <- filename
			con <- file (.self$fileName, "rt")
			txt <- ""
			while (TRUE){
				r <- readLines(con,1)
				if(is.na(r[1])){
					break;
				}
				txt <- paste(txt, r,sep="")
			}
			close(con)
			.self$sourceCode <- txt
			DEBUG("Source code: ", nchar(txt)," characters read")
		}
	) # end of methods
) # end of class


FuzuliLexer <- setRefClass("FuzuliLexer",
				fields = c (
						"fuzuliSource",
						"isDebug", "chars", "tokens", "currentIndex", "oldIndex"
				),
				methods = 
				list (
					initialize = function(fsource){
						fuzuliSource <<- fsource
						.self$chars <- unlist(strsplit(fuzuliSource$sourceCode,""))
						.self$currentIndex <- 1
						.self$oldIndex <- 1
					},

					consume = function(){
						c <- chars[currentIndex]
						currentIndex <<- currentIndex + 1
						return(c)
					},

					putback = function(){
						currentIndex <<- currentIndex - 1
					},

					ischar = function(c){
						if ( (c >= "a" && c <= "z") || (c >= "A" && c <= "Z")){
							return(TRUE)
						}else{
							return(FALSE)
						}
					},

					isnum = function(c){
						if ( (c >= "0" && c <= "9")){
							return(TRUE)
						}else{
							return(FALSE)
						}
					},

					isalnum = function(c){
						if (ischar(c) || isnum(c)){
							return(TRUE)
						}else{
							return(FALSE)
						}
					},

					
					getNextToken = function(){
						if(currentIndex == length(chars)){
							return(NULL)
						}
						cc <- consume()
						if(cc=="\t" || cc=="\r" || cc=="\n" || cc==" "){
							return(getNextToken())
						}else if (cc=="(" || cc==")"){
							return(cc)
						}else if (ischar(cc)){
							cur <- cc
							while(TRUE){
								cc <- consume()
								if(!isalnum(cc)){
									putback()
									return(cur)		
								}
								cur <- paste(cur, cc, sep="")
							}
							return(cur)
						}else if (cc=="'" || cc=="\""){
						    cur <- cc
						    while(TRUE){
						        cc <- consume()
						        cur <- paste(cur, cc, sep="")
                                if(cc=="'" || cc=="\""){
                                    break
                                }
						    }
                            return(cur)
                        }else if (isnum(cc) || cc=="-"){
							cur <- cc
							while(TRUE){
								cc <- consume()
								if(!isnum(cc) && cc!="." && cc!="E" && cc!="-"){
									putback()
									return(cur)		
								}
								cur <- paste(cur, cc, sep="")
							}
							return(cur)
						}else if(cc=="%"){
                            cc <- consume()
                            if(cc=="*"){
                                consume()
                                return("%*%")
                            }else if(cc=="%"){
                                return("%%")
                            }else{
                                putback()
                                return("%")
                            }
                        }else{
							return(cc)
						}
					}
				
				) # end of methods
) # end of class


FuzuliParser <- setRefClass(Class = "FuzuliParser",
    fields = c("lexer"),
    methods= list(
        initialize = function(lexer){
            .self$lexer <- lexer
        },
        getExpressionList = function(){
            exprList <- list()
            while(TRUE){
                currentToken <- .self$lexer$getNextToken()
                if(is.null(currentToken)){
                    return(exprList)
                }
                if(currentToken != "(" && currentToken != ")"){
                    exprList[[length(exprList)+1]] <- currentToken
                }else if(currentToken == "("){
                    exprList[[length(exprList)+1]] <- getExpressionList()
                }else if(currentToken == ")"){
                    return(exprList)
                }
            }
        }, # end of getExpressionList()
        
        run = function(){
            exprs <- getExpressionList()
            result <- NULL
            for (currentExpression in exprs){
                #cat("Running Expr: ", unlist(currentExpression), "\n")
                result <- runExpression(currentExpression)
            }
            return(result)
        }, # end of run
        
        runExpression = function(expr){
            #cat("runExpression called with ", length(expr)," parameters\n")
            #cat("And they are ");print(expr);cat("\n")
            result <- FALSE
            tryCatch(
                {
                    if(!is.na(as.numeric(expr[[1]]))){
                        return(as.numeric(expr[[1]]))
                    }
                }, warning=function(cond){
                    return(TRUE)
                }, error =function(cond) {
                    return(FALSE)
                }
            )
            # if the expression is string literal
            if(unlist(strsplit(expr[[1]],split = ""))[1]=="'"){
                result <- substr(expr[[1]],2, nchar(expr[[1]])-1)
                return(result)
            }else if(expr[[1]]=="print"){
                print(runExpression(expr[[2]]))
                return(TRUE)
            }else if (expr[[1]]=="ifelse" || expr[[1]]=="if"){
                result <- ifelse(runExpression(expr[[2]]), runExpression(expr[[3]]),runExpression(expr[[4]]))
                return(result)
            }else if (expr[[1]]=="let"){
                assign(x = expr[[2]],value = runExpression(expr[[3]]),envir = .GlobalEnv)    
            }else if(expr[[1]]=="="){
                result <- ifelse(runExpression(expr[[2]]) == runExpression(expr[[3]]), TRUE, FALSE)
                return(result)
            }else if(expr[[1]]=="%%"){
                result <- runExpression(expr[[2]]) %% runExpression(expr[[3]])
                return(result)
            }else if(expr[[1]]=="%*%"){
                result <- runExpression(expr[[2]]) %*% runExpression(expr[[3]])
                return(result)
            }else{
                myvar <- get(x = expr[[1]],envir = .GlobalEnv)
                if(!is.function(myvar)){
                    return(myvar)
                }else{
                    evaluated_expr <- list()
                    for (i in 2:length(expr)){
                        evaluated_expr[[i-1]] <- runExpression(expr[[i]])
                    }
                    result <- do.call(myvar,args = evaluated_expr)
                    return(result)
                }
            }
            return(result)
        } # end of runExpression()
        
    ) # end of methods
) # end of class


AutomaticCodeGenerator <- setRefClass(Class="AutomaticCodeGenerator",
    fields = c("FunctionList", "ConstantList"),
    methods = list(
        
        initialize = function(){
            .self$FunctionList <- list()
            .self$ConstantList <- list()
            .self$addFunction("Identity", 1)
        },
        
        addFunction = function(fname, numparams){
            newf <- list(fname = fname, numparams = numparams)
            .self$FunctionList[[length(.self$FunctionList)+1]] <- newf
        },
        
        getFunctionList = function(){
            return(.self$FunctionList)
        },
        
        addConstant = function(name){
            .self$ConstantList[[length(.self$ConstantList)+1]] <- name
        },
        
        generateSingleExpression = function(deep = 1){
            if(deep==0){
                return(sample(.self$ConstantList,size=1))
            }
            randomf <- sample(x = .self$FunctionList,size = 1)[[1]]
            fname <- randomf[["fname"]]
            numparams <- randomf[["numparams"]]
            params <- sample(.self$ConstantList, size=numparams, replace = TRUE)
            txt <- paste("(", fname, sep="")
            for (element in params){
                if(runif(1) < 0.5){
                    txt <- paste(txt, element)
                }else{
                    txt <- paste(txt, generateSingleExpression(deep-1))
                }
            }
            txt <- paste(txt,")",sep="")
            return(txt)
        }
        
        
        
    ) # end of methods
) # end of class

s <- FuzuliSource$new();s$readFile("1.rlisp");l <- FuzuliLexer$new(s);p <- FuzuliParser$new(l);p$run()

x <- c(1,2,3,4,5)
y <- c(2,4,6,8,10)
auto.code <- AutomaticCodeGenerator$new()
auto.code$addConstant("x")
auto.code$addConstant("y")
auto.code$addConstant("2")
auto.code$addFunction("+",2)
auto.code$addFunction("-",2)
auto.code$addFunction("/",2)
auto.code$addFunction("^",2)
auto.code$addFunction("mean",1)
auto.code$addFunction("sum",1)
auto.code$addFunction("length",1)
e <- auto.code$generateSingleExpression(50)
print(e)
s <- FuzuliSource$new();s$readString(e);l <- FuzuliLexer$new(s);p <- FuzuliParser$new(l);result<-p$run()
print(result)


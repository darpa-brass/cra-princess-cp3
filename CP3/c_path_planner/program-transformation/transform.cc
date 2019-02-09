#include <rose.h> 
#include <string>
#include <sstream>
#include <iostream>

using namespace std;
using namespace SageBuilder;
using namespace SageInterface;

void
addFunctionParam(SgFunctionDeclaration *functionDeclaration, char *s)
{
  SgName paramName = s;
  SgTypeDouble *type = buildDoubleType();
  SgInitializedName *element = buildInitializedName(paramName, type);
  functionDeclaration->prepend_arg(element);
}

void
transformFunctionConstants (SgFunctionDeclaration *functionDeclaration)
{
  Rose_STL_Container<SgNode *> valueList =
    NodeQuery::querySubTree (functionDeclaration, V_SgValueExp);

  /* iterate through each value expression */
  int counter = 0;
  for (Rose_STL_Container<SgNode *>::iterator i = valueList.begin();
       i != valueList.end(); i++) {
    SgValueExp *value = isSgValueExp(*i);
    SgNode *valueParent = NULL;
    
    /* used to check if we have either an int or double value expression */
    SgIntVal *intValue = isSgIntVal(*i);
    SgDoubleVal *doubleValue = isSgDoubleVal(*i);

    if((value != NULL) && ((intValue != NULL) || (doubleValue != NULL))) {
      /* Get parent node */
      valueParent = value->get_parent();

      SgPntrArrRefExp *exp = isSgPntrArrRefExp(valueParent);
      if(exp != NULL) {
        continue;
      }

      /* Create replacement var exp */
      char s[32];
      sprintf(s, "ctrlConst%d", counter);
      SgVarRefExp *varRef = buildVarRefExp(s);

      /* is the parent an expression? */
      SgExpression *parentExp = isSgExpression(valueParent);

      if(parentExp != NULL) {
        parentExp->replace_expression(value, varRef);
        addFunctionParam(functionDeclaration, s);  
      } else { // the parent is a statement?
        SgStatement *parentStatement = isSgStatement(valueParent);
        if(parentStatement != NULL) {
          parentStatement->replace_expression(value, varRef);
          addFunctionParam(functionDeclaration, s);
        } else {
          printf("Parent was NULL, counter=%d\n", counter);
        }
      }
      counter++;
    } else {
      printf("Value was NULL, counter=%d\n", counter);
    }
  } 
}

void
transformFunctionLoops (SgFunctionDeclaration *functionDeclaration)
{
  /* query for while loops */
  Rose_STL_Container<SgNode *> whileList =
    NodeQuery::querySubTree (functionDeclaration, V_SgWhileStmt);

  /* query for for loops */
  Rose_STL_Container<SgNode *> forList =
    NodeQuery::querySubTree (functionDeclaration, V_SgForStatement);

  /* iterate through each for statement */
  int counter = 0;
  for (Rose_STL_Container<SgNode *>::iterator i = forList.begin();
       i != forList.end(); i++) {
    SgForStatement *forStmt = isSgForStatement(*i);

    if(forStmt == NULL) {
      continue;
    }
 
    SgStatement *condition = forStmt->get_test();

    if(condition == NULL) {
      continue;
    }

    SgExprStatement *exprStmt = isSgExprStatement(condition);
    
    if(exprStmt == NULL) {
      continue;
    }

    SgBinaryOp *binaryOp = isSgBinaryOp(exprStmt->get_expression());

    if(binaryOp == NULL) {
      continue;
    }
    
    SgExpression *rhs = binaryOp->get_rhs_operand();

    /* Create var exp */
    char s[32];
    sprintf(s, "ctrlLoop%d", counter);
    SgVarRefExp *varRef = buildVarRefExp(s);

    /* create binary addition operation */
    SgAddOp *addOp = buildAddOp(rhs, varRef);

    /* replace prvious rhs of condition with new expr */
    binaryOp->replace_expression(rhs, addOp);

    /* add new function parameter */
    addFunctionParam(functionDeclaration, s);

    counter++;
  }

  /* iterate through each while statement */
  for (Rose_STL_Container<SgNode *>::iterator i = whileList.begin();
       i != whileList.end(); i++) {
    SgWhileStmt *whileStmt = isSgWhileStmt(*i);

    if(whileStmt == NULL) {
      continue;
    }

    SgStatement *condition = whileStmt->get_condition();

    if(condition == NULL) {
      continue;
    }

    SgExprStatement *exprStmt = isSgExprStatement(condition);

    if(exprStmt == NULL) {
      continue;
    }

    SgBinaryOp *binaryOp = isSgBinaryOp(exprStmt->get_expression());
   
    if(binaryOp == NULL) {
      continue;
    }

    SgExpression *rhs = binaryOp->get_rhs_operand();

    /* Create var exp */
    char s[32];
    sprintf(s, "ctrlLoop%d", counter);
    SgVarRefExp *varRef = buildVarRefExp(s);

    /* create binary addition operation */
    SgAddOp *addOp = buildAddOp(rhs, varRef);

    /* replace prvious rhs of condition with new expr */
    binaryOp->replace_expression(rhs, addOp);

    /* add new function parameter */
    addFunctionParam(functionDeclaration, s);

    counter++;
  }
}

void
transformFunctionConditionals (SgFunctionDeclaration *functionDeclaration)
{
  /* query for if statements */
  Rose_STL_Container<SgNode *> ifList =
    NodeQuery::querySubTree (functionDeclaration, V_SgIfStmt);

  int counter = 0;
  /* iterate through each if statement */
  for (Rose_STL_Container<SgNode *>::iterator i = ifList.begin();
       i != ifList.end(); i++) {
    SgIfStmt *ifStmt = isSgIfStmt(*i);

    if(ifStmt == NULL) {
      continue;
    }

    SgStatement *condition = ifStmt->get_conditional();

    if(condition == NULL) {
      continue;
    }

    SgExprStatement *exprStmt = isSgExprStatement(condition);

    if(exprStmt == NULL) {
      continue;
    }

    SgBinaryOp *binaryOp = isSgBinaryOp(exprStmt->get_expression());

    if(binaryOp == NULL) {
      continue;
    }

    SgExpression *rhs = binaryOp->get_rhs_operand();

    /* Create var exp */
    char s[32];
    sprintf(s, "ctrlCmp%d", counter);
    SgVarRefExp *varRef = buildVarRefExp(s);

    /* create binary addition operation */
    SgAddOp *addOp = buildAddOp(rhs, varRef);

    /* replace prvious rhs of condition with new expr */
    binaryOp->replace_expression(rhs, addOp);

    /* add new function parameter */
    addFunctionParam(functionDeclaration, s);

    counter++;
  }
}

void
transformFunction (SgFunctionDeclaration *functionDeclaration)
{
  transformFunctionConstants (functionDeclaration);
  transformFunctionLoops (functionDeclaration);
  transformFunctionConditionals (functionDeclaration);
}

int
main (int argc, char *argv[])
{
  /* Initialize */
  ROSE_INITIALIZE;

  /* Build the AST used by ROSE */
  SgProject *project = frontend (argc, argv);
  //ROSE_ASSERT (project != NULL);

  /* Build a list of functions within the AST */
  Rose_STL_Container<SgNode *> functionDeclarationList =
    NodeQuery::querySubTree (project, V_SgFunctionDeclaration);

  /* Iterate through list of function declarations found */
  int counter = 0;
  for (Rose_STL_Container<SgNode *>::iterator i = 
         functionDeclarationList.begin(); 
       i != functionDeclarationList.end();
       i++) {
    
    /* Build pointer to function declaration type reference */
    SgFunctionDeclaration *functionDeclaration = isSgFunctionDeclaration(*i);
    //ROSE_ASSERT(functionDeclaration != NULL);

    /* Only process functions that are not compiler generated */
    if ((*i)->get_file_info()->isCompilerGenerated() == false) {
      /* TODO: transform each function */
      printf ("Function #%2d name is %s at line %d\n",
              counter++, functionDeclaration->get_name().str(),
              functionDeclaration->get_file_info()->get_line());
      /* Transform this function */
      if(functionDeclaration->get_name() != "main") {
        transformFunction (functionDeclaration);
      }
    }
  }

  project->unparse();
  return 0; //backend(project);
}
  

//
// Created by Michal Young on 9/12/18.
//

#include "ASTNode.h"

namespace AST {
    // Abstract syntax tree.  ASTNode is abstract base class for all other nodes.


    // JSON representation of all the concrete node types.
    // This might be particularly useful if I want to do some
    // tree manipulation in Python or another language.  We'll
    // do this by emitting into a stream.

    // --- Utility functions used by node-specific json output methods

    /* Indent to a given level */
    void ASTNode::json_indent(std::ostream& out, AST_print_context& ctx) {
        if (ctx.indent_ > 0) {
            out << std::endl;
        }
        for (int i=0; i < ctx.indent_; ++i) {
            out << "    ";
        }
    }

    /* The head element looks like { "kind" : "block", */
    void ASTNode::json_head(std::string node_kind, std::ostream& out, AST_print_context& ctx) {
        json_indent(out, ctx);
        out << "{ \"kind\" : \"" << node_kind << "\"," ;
        ctx.indent();  // one level more for children
        return;
    }

    void ASTNode::json_close(std::ostream& out, AST_print_context& ctx) {
        // json_indent(out, ctx);
        out << "}";
        ctx.dedent();
    }

    void ASTNode::json_child(std::string field, ASTNode& child, std::ostream& out, AST_print_context& ctx, char sep) {
        json_indent(out, ctx);
        out << "\"" << field << "\" : ";
        child.json(out, ctx);
        out << sep;
    }

    void Stub::json(std::ostream& out, AST_print_context& ctx) {
        json_head("Stub", out, ctx);
        json_indent(out, ctx);
        out  << "\"rule\": \"" <<  name_ << "\"";
        json_close(out, ctx);
    }


    void Program::json(std::ostream &out, AST::AST_print_context &ctx) {
        json_head("Program", out, ctx);
        json_child("classes_", classes_, out, ctx);
        json_child("statements_", statements_, out, ctx, ' ');
        json_close(out, ctx);
    }

    void Formal::json(std::ostream &out, AST::AST_print_context &ctx) {
        json_head("Formal", out, ctx);
        json_child("var_", var_, out, ctx);
        json_child("type_", type_, out, ctx, ' ');
        json_close(out, ctx);
    }

    void Method::json(std::ostream &out, AST::AST_print_context &ctx) {
        json_head("Method", out, ctx);
        json_child("name_", name_, out, ctx);
        json_child("formals_", formals_, out, ctx);
        json_child("returns_", returns_, out, ctx);
        json_child("statements_", statements_, out, ctx, ' ');
        json_close(out, ctx);
    }

    void Assign::json(std::ostream& out, AST_print_context& ctx) {
        json_head("Assign", out, ctx);
        json_child("lexpr_", lexpr_, out, ctx);
        json_child("rexpr_", rexpr_, out, ctx, ' ');
        json_close(out, ctx);
     }

    void AssignDeclare::json(std::ostream& out, AST_print_context& ctx) {
        json_head("Assign", out, ctx);
        json_child("lexpr_", lexpr_, out, ctx);
        json_child("rexpr_", rexpr_, out, ctx);
        json_child("static_type_", static_type_, out, ctx, ' ');
        json_close(out, ctx);
    }

    void Return::json(std::ostream &out, AST::AST_print_context &ctx) {
        json_head("Return", out, ctx);
        json_child("expr_", expr_, out, ctx, ' ');
        json_close(out, ctx);
    }

    void If::json(std::ostream& out, AST_print_context& ctx) {
        json_head("If", out, ctx);
        json_child("cond_", cond_, out, ctx);
        json_child("truepart_", truepart_, out, ctx);
        json_child("falsepart_", falsepart_, out, ctx, ' ');
        json_close(out, ctx);
    }

    void While::json(std::ostream& out, AST_print_context& ctx) {
        json_head("While", out, ctx);
        json_child("cond_", cond_, out, ctx);
        json_child("body_", body_, out, ctx, ' ');
        json_close(out, ctx);
    }


    void Typecase::json(std::ostream& out, AST_print_context& ctx) {
        json_head("Typecase", out, ctx);
        json_child("expr_", expr_, out, ctx);
        json_child("cases_", cases_, out, ctx, ' ');
        json_close(out, ctx);
    }

    void Type_Alternative::json(std::ostream& out, AST_print_context& ctx) {
        json_head("Type_Alternative", out, ctx);
        json_child("ident_", ident_, out, ctx);
        json_child("classname_", classname_, out, ctx);
        json_child("block_", block_, out, ctx, ' ');
        json_close(out, ctx);
    }

    void Load::json(std::ostream &out, AST::AST_print_context &ctx) {
        json_head("Load", out, ctx);
        json_child("loc_", loc_, out, ctx, ' ');
        json_close(out, ctx);
    }

    void Ident::json(std::ostream& out, AST_print_context& ctx) {
        json_head("Ident", out, ctx);
        out << "\"text_\" : \"" << text_ << "\"";
        json_close(out, ctx);
    }

    void Class::json(std::ostream &out, AST::AST_print_context &ctx) {
        json_head("Class", out, ctx);
        json_child("name_", name_, out, ctx);
        json_child("super_", super_, out, ctx);
        json_child("constructor_", constructor_, out, ctx);
        json_child("methods_", methods_, out, ctx, ' ');
        json_close(out, ctx);
    }

    void Call::json(std::ostream &out, AST::AST_print_context &ctx) {
        json_head("Call", out, ctx);
        json_child("obj_", receiver_, out, ctx);
        json_child("method_", method_, out, ctx);
        json_child("actuals_", actuals_, out, ctx, ' ');
        json_close(out, ctx);
    }

    void Construct::json(std::ostream &out, AST::AST_print_context &ctx) {
        json_head("Construct", out, ctx);
        json_child("method_", method_, out, ctx);
        json_child("actuals_", actuals_, out, ctx, ' ');
        json_close(out, ctx);
    }

    void IntConst::json(std::ostream& out, AST_print_context& ctx) {
        json_head("IntConst", out, ctx);
        out << "\"value_\" : " << value_ ;
        json_close(out, ctx);
    }

    void StrConst::json(std::ostream& out, AST_print_context& ctx) {
        json_head("StrConst", out, ctx);
        out << "\"value_\" : \"" << value_  << "\"";
        json_close(out, ctx);
    }


    void BinOp::json(std::ostream& out, AST_print_context& ctx) {
        json_head(opsym, out, ctx);
        json_child("left_", left_, out, ctx);
        json_child("right_", right_, out, ctx, ' ');
        json_close(out, ctx);
    }


    void Not::json(std::ostream& out, AST_print_context& ctx) {
        json_head("Not", out, ctx);
        json_child("left_", left_, out, ctx, ' ');
        json_close(out, ctx);
    }

    void Dot::json(std::ostream& out, AST_print_context& ctx) {
        json_head("Dot", out, ctx);
        json_child("left_", left_, out, ctx);
        json_child("right_", right_, out, ctx, ' ');
        json_close(out, ctx);
    }


    void Block::gen_rvalue(CodegenContext& ctx, std::string target_reg) {
        std::string used_reg;
        used_reg.assign(target_reg);
        for (auto &s: elements_) {
            s->gen_rvalue(ctx, used_reg);
            std::string reg = ctx.alloc_reg();
            used_reg.assign(reg);
        }
    }

    void IntConst::gen_rvalue(CodegenContext &ctx, std::string target_reg) {
        int cur_reg = ctx.get_current_reg_number();
        ctx.change_reg_type(cur_reg, 1);
        ctx.emit(target_reg + "=int_literal(" + std::to_string(value_) + ");");
    }

    void StrConst::gen_rvalue(CodegenContext &ctx, std::string target_reg){
      int cur_reg = ctx.get_current_reg_number();
      ctx.change_reg_type(cur_reg, 2);
      ctx.emit(target_reg + "=str_literal(" + value_ + ");");
    }

    void Program::gen_rvalue(CodegenContext &ctx, std::string target_reg) {
      statements_.gen_rvalue(ctx, target_reg);
    }

    void Actuals::gen_rvalue(CodegenContext& ctx, std::string target_reg){
      for (auto &s: elements_) {
        std::string new_reg = ctx.alloc_reg();
        s->gen_rvalue(ctx, new_reg);
      }
    }

    void Call::gen_rvalue(CodegenContext &ctx, std::string target_reg){
      receiver_.gen_rvalue(ctx, target_reg);
      std::string start_from_reg = ctx.get_num_reg(ctx.get_current_reg_number());
      int start_from = ctx.get_current_reg_number() + 1;
      std::string method_name;
      method_name.assign(method_.get_text());
      actuals_.gen_rvalue(ctx, target_reg);
      int end = ctx.get_current_reg_number();
      int i;
      std::string receiver_part;
      std::string args;
      int static_for_return;

      //integer to represent type, 1 for int, 2 for string,
      //3 for boolean and 0 for obj

      if(ctx.get_reg_type(start_from - 1) == 1){ //this is an int
        args = "(obj_Int) " + start_from_reg;
        if(method_name.compare("STRING") == 0){
          static_for_return = 2;
        }else if(method_name.compare("EQUALS") == 0){
          static_for_return = 3;
        }else if(method_name.compare("LESS") == 0){
          static_for_return = 3;
        }else if(method_name.compare("PLUS") == 0){
          static_for_return = 1;
        }
      }else if(ctx.get_reg_type(start_from - 1) == 0){
        args = "(obj_Obj) " + start_from_reg;
        if(method_name.compare("STRING") == 0){
          static_for_return = 2;
        }else if(method_name.compare("PRINT") == 0){
          static_for_return = 0;
        }else if(method_name.compare("EQUALS") == 0){
          static_for_return = 3;
        }
      }else if(ctx.get_reg_type(start_from-1) == 2){
        args = "(obj_String) " + start_from_reg;
        if(method_name.compare("STRING") == 0){
          static_for_return = 2;
        }else if(method_name.compare("PRINT") == 0){
          static_for_return = 2;
        }else if(method_name.compare("EQUALS") == 0){
          static_for_return = 3;
        }
      }else if(ctx.get_reg_type(start_from - 1) == 3){
        args = "(obj_Boolean) " + start_from_reg;
      }
      receiver_part.assign(args);
      if(start_from - 1 != end){
        args.append(", ");
      }
      for (i=start_from;i<=end;i++){
        if(i != end){
          if(ctx.get_reg_type(i) == 1){
            args.append("(obj_Int) ");
          }else if(ctx.get_reg_type(i) == 0){
            args.append("(obj_Obj) ");
          }else if(ctx.get_reg_type(i) == 2){
            args.append("(obj_String) ");
          }
          args.append("tmp__");
          args.append(std::to_string(i));
          args.append(", ");
        }
        else{
          if(ctx.get_reg_type(i) == 1){
            args.append("(obj_Int) ");
          }else if(ctx.get_reg_type(i) == 0){
            args.append("(obj_Obj) ");
          }else if(ctx.get_reg_type(i) == 2){
            args.append("(obj_String) ");
          }
          args.append("tmp__");
          args.append(std::to_string(i));
        }
      }
      std::string call_reg = ctx.alloc_reg();
      int call_reg_num = ctx.get_current_reg_number();
      ctx.change_reg_type(call_reg_num,static_for_return);
      ctx.emit(call_reg + "= (obj_Obj) ("+ receiver_part + ")->clazz->" + method_name + "(" + args + ");");
    }

    void Load::gen_rvalue(CodegenContext &ctx, std::string target_reg){

    }

    void Assign::gen_rvalue(CodegenContext &ctx, std::string target_reg){
      rexpr_.gen_rvalue(ctx, target_reg);
    }
    void AssignDeclare::gen_rvalue(CodegenContext &ctx, std::string target_reg){
      rexpr_.gen_rvalue(ctx, target_reg);
    }

    /* Convenience factory for operations like +, -, *, / */
    Call* Call::binop(std::string opname, Expr& receiver, Expr& arg) {
        Ident* method = new Ident(opname);
        Actuals* actuals = new Actuals();
        actuals->append(&arg);
        return new Call(receiver, *method, *actuals);
    }
}

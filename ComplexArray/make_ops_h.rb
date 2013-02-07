
op_rev = %w(+ *) # switchable operator
op_seq = %w(- /) # nonswitchable operator
ops=op_rev + op_seq
vars=%w(double Complex^)
arrs=%w(ComplexArray^)

open("ops.h","w")do |out|
  $stdout = out

  puts "// for header file"

  ops.each do |op|
    puts "    // Definitions of operator #{op}"
    vars.each do |klass|
      puts "    static ComplexArray^ operator #{op}(ComplexArray^ lhs, #{klass} rhs);"
      puts "    static ComplexArray^ operator #{op}(#{klass} lhs, ComplexArray^ rhs);"
    end
    arrs.each do |klass|
      puts "    static ComplexArray^ operator #{op}(ComplexArray^ lhs, #{klass} rhs);"
    end
    puts
  end

end

#puts "// for source file"

open("ComplexArray_operators.cpp","w") do |out|

  $stdout = out
  puts <<-NNN
#include "Stdafx.h"
#include "ComplexArray.h"

BEGIN_NAMESPACE;

  NNN

  op_rev.each do |op|
    puts "\n// Implimentations of operator #{op} "
    vars.each do |klass|
      puts <<-NNN

ComplexArray^ ComplexArray::operator #{op}(ComplexArray^ lhs, #{klass} rhs)
{
  // allocate results without initialization
  ComplexArray^ res = gcnew ComplexArray(lhs->size_, false);
  // Apply operation and return
  for(int i = 0; i < lhs->Length; ++i){
    res[i] = lhs[i] #{op} rhs;
  }
  return res;
}

ComplexArray^ ComplexArray::operator #{op}(#{klass} lhs, ComplexArray^ rhs)
{
    return rhs #{op} lhs;
}

      NNN
    end
    arrs.each do |klass|
      puts <<-NNN

ComplexArray^ ComplexArray::operator #{op}(ComplexArray^ lhs, #{klass} rhs)
{
  // Size Check
  if(lhs->size_ != rhs->size_) throw gcnew ArgumentException("Need same length ComplexArrays.");
  // allocate results without initialization
  ComplexArray^ res = gcnew ComplexArray(lhs->size_, false);
  // Apply operation and return
  for(int i = 0; i < lhs->Length; ++i){
    res[i] = lhs[i] #{op} rhs[i];
  }
  return res;
}
      NNN
    end
  end
  op_seq.each do |op|
    vars.each do |klass|
      puts <<-NNN

ComplexArray^ ComplexArray::operator #{op}(ComplexArray^ lhs, #{klass} rhs)
{
  // allocate results without initialization
  ComplexArray^ res = gcnew ComplexArray(lhs->size_, false);
  // Apply operation and return
  for(int i = 0; i < lhs->Length; ++i){
    res[i] = lhs[i] #{op} rhs;
  }
  return res;
}

ComplexArray^ ComplexArray::operator #{op}(#{klass} lhs, ComplexArray^ rhs)
{
  // allocate results without initialization
  ComplexArray^ res = gcnew ComplexArray(rhs->size_, false);
  // Apply operation
  for(int i = 0; i < res->Length; ++i){
    res[i] = lhs #{op} rhs[i];
  }
  return res;
}

      NNN
    end
    arrs.each do |klass|
      puts <<-NNN

ComplexArray^ ComplexArray::operator #{op}(ComplexArray^ lhs, #{klass} rhs)
{
  // Size Check
  if(lhs->size_ != rhs->size_) throw gcnew ArgumentException("Need same length ComplexArrays.");
  // allocate results without initialization
  ComplexArray^ res = gcnew ComplexArray(lhs->size_, false);
  // Apply operation and return
  for(int i = 0; i < lhs->Length; ++i){
    res[i] = lhs[i] #{op} rhs[i];
  }
  return res;
}
      NNN
    end
  end

  puts "\n\nEND_NAMESPACE;\n"
end


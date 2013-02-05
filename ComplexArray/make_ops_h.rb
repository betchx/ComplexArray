
op_rev = %w(+ *) # switchable operator
op_seq = %w(- /) # nonswitchable operator
ops=op_rev + op_seq
vars=%w(double IComplex^ IComplex%)
arrs=%w(ComplexArray^ ComplexArray%)

puts "// for header file"

ops.each do |op|
  puts "    // Definitions of operator #{op}"
  vars.each do |klass|
    puts "    ComplexArray^ operator #{op}(#{klass} rhs);"
    puts "    static ComplexArray^ operator #{op}(#{klass} lhs, ComplexArray^ rhs);"
    puts "    static ComplexArray^ operator #{op}(#{klass} lhs, ComplexArray% rhs);"
  end
  arrs.each do |klass|
    puts "    ComplexArray^ operator #{op}(#{klass} rhs);"
  end
  puts
end

puts "// for source file"

op_rev.each do |op|
  puts "\n// Implimentations of operator #{op} "
  vars.each do |klass|
    puts <<-NNN

ComplexArray^ ComplexArray::operator #{op}(#{klass} rhs)
{
  // Cleate Clone
  ComplexArray^ res = gcnew ComplexArray(size_, false);
  // Apply operation and return
  for(int i = 0; i < Length; ++i){
    res[i] = this[i] #{op} rhs;
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

ComplexArray^ ComplexArray::operator #{op}(#{klass} rhs)
{
  // Cleate Clone
  ComplexArray^ res = gcnew ComplexArray(size_, false);
  // Apply operation and return
  for(int i = 0; i < Length; ++i){
    res[i] = this[i] #{op} rhs[i];
  }
  return res;
}
NNN
  end
end
op_seq.each do |op|
  vars.each do |klass|
    puts <<-NNN

ComplexArray^ ComplexArray::operator #{op}(#{klass} rhs)
{
  // Cleate Clone
  ComplexArray^ res = gcnew ComplexArray(size_, false);
  // Apply operation and return
  for(int i = 0; i < Length; ++i){
    res[i] = this[i] #{op} rhs;
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

ComplexArray^ ComplexArray::operator #{op}(#{klass} rhs)
{
  // Cleate Clone
  ComplexArray^ res = gcnew ComplexArray(size_, false);
  // Apply operation and return
  for(int i = 0; i < Length; ++i){
    res[i] = this[i] #{op} rhs[i];
  }
  return res;
}
NNN
  end
end


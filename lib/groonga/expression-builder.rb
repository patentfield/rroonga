# -*- coding: utf-8 -*-
#
# Copyright (C) 2009  Kouhei Sutou <kou@clear-code.com>
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License version 2.1 as published by the Free Software Foundation.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

module Groonga
  module ExpressionBuildable
    attr_reader :table
    attr_accessor :query
    attr_accessor :parser

    def initialize(*args)
      @table = nil
      @name = nil
      @query = nil
      @parser = nil
      @default_column = nil
    end

    def build
      expression = Expression.new(:name => @name)
      variable = expression.define_variable(:domain => @table)

      builder = nil
      builder = match(@query, :parser => @parser) if @query
      if block_given?
        if builder
          builder &= yield(self)
        else
          builder = yield(self)
        end
      end
      if builder.nil? or builder == self
        expression.append_constant(1)
        expression.append_constant(1)
        expression.append_operation(Groonga::Operation::OR, 2)
      else
        builder.build(expression, variable)
      end

      expression.compile
      expression
    end

    class ExpressionBuilder
      def initialize
        super()
      end

      def &(other)
        AndExpressionBuilder.new(self, other)
      end

      def |(other)
        OrExpressionBuilder.new(self, other)
      end
    end

    class SetExpressionBuilder < ExpressionBuilder
      def initialize(operation, *expression_builders)
        super()
        @operation = operation
        @expression_builders = expression_builders
      end

      def build(expression, variable)
        return if @expression_builders.empty?
        @expression_builders.each do |builder|
          builder.build(expression, variable)
        end
        expression.append_operation(@operation, @expression_builders.size)
      end
    end

    class AndExpressionBuilder < SetExpressionBuilder
      def initialize(*expression_builders)
        super(Groonga::Operation::AND, *expression_builders)
      end
    end

    class OrExpressionBuilder < SetExpressionBuilder
      def initialize(*expression_builders)
        super(Groonga::Operation::OR, *expression_builders)
      end
    end

    class BinaryExpressionBuilder < ExpressionBuilder
      def initialize(operation, column_name, value)
        super()
        @operation = operation
        @column_name = column_name
        @value = value
      end

      def build(expression, variable)
        expression.append_object(variable)
        expression.append_constant(@column_name)
        expression.append_operation(Groonga::Operation::GET_VALUE, 2)
        expression.append_constant(@value)
        expression.append_operation(@operation, 2)
      end
    end

    class EqualExpressionBuilder < BinaryExpressionBuilder
      def initialize(column_name, value)
        super(Groonga::Operation::EQUAL, column_name, value)
      end
    end

    class MatchExpressionBuilder < BinaryExpressionBuilder
      def initialize(column_name, value)
        super(Groonga::Operation::MATCH, column_name, value)
      end
    end

    class LessExpressionBuilder < BinaryExpressionBuilder
      def initialize(column_name, value)
        super(Groonga::Operation::LESS, column_name, value)
      end
    end

    class LessEqualExpressionBuilder < BinaryExpressionBuilder
      def initialize(column_name, value)
        super(Groonga::Operation::LESS_EQUAL, column_name, value)
      end
    end

    class GreaterExpressionBuilder < BinaryExpressionBuilder
      def initialize(column_name, value)
        super(Groonga::Operation::GREATER, column_name, value)
      end
    end

    class GreaterEqualExpressionBuilder < BinaryExpressionBuilder
      def initialize(column_name, value)
        super(Groonga::Operation::GREATER_EQUAL, column_name, value)
      end
    end

    class SubExpressionBuilder < ExpressionBuilder
      def initialize(query, options)
        super()
        @query = query
        @options = options
      end

      def build(expression, variable)
        expression.parse(@query, @options)
      end
    end
  end

  class RecordExpressionBuilder
    include ExpressionBuildable

    def initialize(table, name)
      super()
      @table = table
      @name = name
    end

    def [](name)
      column = @table.column(name)
      if column.nil?
        message = "unknown column <#{name.inspect}> " +
          "for table <#{@table.inspect}>"
        raise ArgumentError, message
      end
      ColumnExpressionBuilder.new(column, nil, nil)
    end

    def match(query, options_or_default_column={})
      if options_or_default_column.is_a?(String)
        options = {:default_column => options_or_default_column}
      else
        options = options_or_default_column
      end
      options = options.dup
      options[:parser] ||= :query
      SubExpressionBuilder.new(query, options)
    end
  end

  class ColumnExpressionBuilder
    include ExpressionBuildable

    def initialize(column, name, query)
      super()
      @table = column.table
      @range = column.range
      @column = column
      @default_column = column.local_name
      @name = name
      @query = query
    end

    def ==(other)
      EqualExpressionBuilder.new(@default_column, normalize(other))
    end

    def =~(other)
      MatchExpressionBuilder.new(@default_column, normalize(other))
    end

    def <(other)
      LessExpressionBuilder.new(@default_column, normalize(other))
    end

    def <=(other)
      LessEqualExpressionBuilder.new(@default_column, normalize(other))
    end

    def >(other)
      GreaterExpressionBuilder.new(@default_column, normalize(other))
    end

    def >=(other)
      GreaterEqualExpressionBuilder.new(@default_column, normalize(other))
    end

    def match(query, options={})
      options = options.dup
      options[:parser] ||= :query
      options[:default_column] = @default_column
      SubExpressionBuilder.new(query, options)
    end

    private
    def normalize(other)
      if @range.is_a?(Groonga::Table) and other.is_a?(Integer)
        Groonga::Record.new(@range, other)
      else
        other
      end
    end
  end
end

class Node

  attr_reader :name, :successors

  def initialize(name)
    @name = name
    @successors = []
  end

  def add_edge(successor)
    @successors << successor
  end

  def to_s
    "#{@name} -> [#{@successors.map(&:name).join(' ')}]"
  end

end